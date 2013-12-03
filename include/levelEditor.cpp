#include "levelEditor.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "utilities/converter.hpp"

#include <sstream>

LevelEditor::LevelEditor(sf::RenderWindow &window):
	m_window(window), m_xOffset(0), m_yOffset(0), m_currentColor(0), m_drawMode(DrawMode::nothing), m_selectedXPos(0), m_selectedScript(nullptr)
{
	init();
}

void LevelEditor::init()
{
	for(std::size_t i = 0; i < m_display.size(); i++)
	{
		int col = i;
		while(col >= 32)
		{
			col -= 32;
		}

		m_display[i].setPosition(col * 25, static_cast<int>(i / 32) * 25); 
		m_display[i].setSize(sf::Vector2f(25.f, 25.f));
		m_display[i].setOutlineThickness(1.f);
		m_display[i].setOutlineColor(sf::Color::White);
		m_display[i].setFillColor(sf::Color(0,0,0,0));
	}

	for(std::size_t i = 0; i < 32; i++)
	{
		m_lines.push_back(LevelLine());
	}

	updateDisplay();

	//Init interface
	m_font.loadFromFile("data/fonts/DejaVuSans.ttf");

	m_displayOffset.setFont(m_font);
	m_displayOffset.setPosition(10, 460);
	m_displayOffset.setString("Grid left upper corner : 0 | 0");
	m_displayOffset.setCharacterSize(20);
	m_displayOffset.setColor(sf::Color::White);

	m_displayMousePos.setFont(m_font);
	m_displayMousePos.setPosition(10, 485);
	m_displayMousePos.setString("Mouse position : 0 | 0");
	m_displayMousePos.setCharacterSize(20);
	m_displayMousePos.setColor(sf::Color::White);


	//Display last colors
	for(std::size_t i = 0; i < m_displayLastColors.size(); i++)
	{
		int col = i;
		while(col > 4)
		{
			col -= 5;
		}

		m_displayLastColors[i].setSize(sf::Vector2f(25.f,25.f));
		m_displayLastColors[i].setPosition(950 + (col*25), 375 + (static_cast<int>(i / 5.f)*25));
		m_displayLastColors[i].setOutlineThickness(1);
		m_displayLastColors[i].setOutlineColor(sf::Color::Black);
		m_displayLastColors[i].setFillColor(sf::Color::White);
	}

	setCurrentColor(sf::Color::White);
}

void LevelEditor::keyInput(const sf::Event &event)
{
	if(event.type == sf::Event::TextEntered)
	{
		if(event.text.unicode < 128)
		{
			char sign = static_cast<char>(event.text.unicode);
			
			if(sign == 'W' || sign == 'w')
			{
				if(m_yOffset > 0)
					m_yOffset--;
			}
			else if(sign == 'S' || sign == 's')
			{
				if(m_yOffset < 200)
					m_yOffset++;
			}
			else if(sign == 'A' || sign == 'a')
			{
				if(m_xOffset > 0)
					m_xOffset--;
			}
			else if(sign == 'D' || sign == 'd')
			{
				if(m_xOffset < 1000000)
				{
					m_xOffset++;
					if(m_xOffset + 32 > m_lines.size())
					{
						m_lines.push_back(LevelLine());
					}

				}
			}
		}

		updateDisplay();

	}

}


void LevelEditor::mouseInput()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	
		if(mousePos.x < 800 && mousePos.y < 450 && mousePos.x > 0 && mousePos.y > 0)
		{
			int col = static_cast<int>(mousePos.x / 25.f);
			int row = static_cast<int>(mousePos.y / 25.f);

			if(m_drawMode == DrawMode::opticalBlock)
			{
				if(m_currentColor != -1)
					m_lines[m_xOffset + col].addColor(m_yOffset + row, m_currentColor);
			}
			else if(m_drawMode == DrawMode::collisionBlock)
			{
				m_lines[m_xOffset + col].addCollisionType(m_yOffset + row, CollisionType::COLLISION);
			}
			else if(m_drawMode == DrawMode::finishBlock)
			{
				m_lines[m_xOffset + col].addCollisionType(m_yOffset + row, CollisionType::FINISH);
			}
			else if(m_drawMode == DrawMode::scripts)
			{
				m_selectedXPos = col + m_xOffset;
				m_selectedScript = nullptr;
			}
		}

		//Check last colors
		if(m_drawMode == DrawMode::collisionBlock || m_drawMode == DrawMode::opticalBlock || m_drawMode == DrawMode::finishBlock)
		{
			if(mousePos.x >= 950 && mousePos.y <= 1050 && mousePos.y >= 375 && mousePos.y <= 475)
			{
				int col = static_cast<int>((mousePos.x - 950) / 25.f);
				int row = static_cast<int>((mousePos.y - 375) / 25.f);
				setCurrentColor(m_displayLastColors[(row*5)+col].getFillColor());
			}

		}

	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	
		if(mousePos.x < 800 && mousePos.y < 450 && mousePos.x > 0 && mousePos.y > 0)
		{
			int col = static_cast<int>(mousePos.x / 25.f);
			int row = static_cast<int>(mousePos.y / 25.f);

			if(m_drawMode == DrawMode::opticalBlock)
			{
				m_lines[m_xOffset + col].addColor(m_yOffset + row, -1);
			}
			else if(m_drawMode == DrawMode::finishBlock || m_drawMode == DrawMode::collisionBlock)
			{
				m_lines[m_xOffset + col].addCollisionType(m_yOffset + row, CollisionType::NONE);
			}


		}
	}


	updateDisplay();
}



void LevelEditor::render()
{
	//Draw positions display
	updateTexts();
	m_window.draw(m_displayMousePos);
	m_window.draw(m_displayOffset);

	//Draw Editor
	for(auto &it : m_display)
	{
		m_window.draw(it);
	}

	//Draw last color

	if(m_drawMode == DrawMode::collisionBlock || m_drawMode == DrawMode::opticalBlock || m_drawMode == DrawMode::finishBlock)
	{
		for(auto &it : m_displayLastColors)
		{
			m_window.draw(it);
		}

	}


	// Draw overlays
	if(m_drawMode == DrawMode::collisionBlock || m_drawMode == DrawMode::finishBlock)
	{
		//Draw the overlay for collision and finish blocks!
		for(std::size_t i = 0; i < m_display.size(); i++)
		{
			int col = i;

			while(col >= 32)
			{
				col -= 32;
			}
		
			int row = static_cast<int>(i/32.f);

			if(m_lines[m_xOffset + col].getCollisionType(m_yOffset + row) == CollisionType::COLLISION)
			{
				sf::RectangleShape temp = m_display[i];
				temp.setFillColor(sf::Color(255,0,0,120));
				m_window.draw(temp);
			}
			else if(m_lines[m_xOffset + col].getCollisionType(m_yOffset + row) == CollisionType::FINISH)
			{
				sf::RectangleShape temp = m_display[i];
				temp.setFillColor(sf::Color(0,255,0,120));
				m_window.draw(temp);
			}
		}
	}
	else if(m_drawMode == DrawMode::scripts)
	{
		//Draw scripts overlay
		for(int i = m_xOffset; i < m_xOffset+32; i++)
		{
			if(i == m_selectedXPos)
				continue;

			if(m_scriptManager.isScriptAtXPos(i))
			{
				sf::RectangleShape overlay(sf::Vector2f(25,450));
				overlay.setPosition((i-m_xOffset)*25, 0);
				overlay.setFillColor(sf::Color(255, 255, 0, 120));
				m_window.draw(overlay);
			}

		}

		//Draw the selected Col overlay
		if(m_selectedXPos >= m_xOffset && m_selectedXPos < m_xOffset + 32)
		{
			sf::RectangleShape overlay(sf::Vector2f(25,450));
			overlay.setPosition((m_selectedXPos - m_xOffset) * 25, 0);
			overlay.setFillColor(sf::Color(0, 255, 255, 120));
			m_window.draw(overlay);
		}


	}


	

}


void LevelEditor::addScript()
{
	m_scriptManager.addScript(ScriptType::NOTHING, m_selectedXPos, 0, 0, 0);
}

void LevelEditor::addScript(const Script &script)
{
	m_scriptManager.addScript(script);
}

void LevelEditor::addLevelLine()
{
	m_lines.push_back(LevelLine());
}

void LevelEditor::addBlockToLastLine(int yPos, int color, CollisionType type)
{
	m_lines.back().addColor(yPos, color);
	m_lines.back().addCollisionType(yPos, type);
}

void LevelEditor::addColor(const sf::Color &color)
{
	m_colors.push_back(color);
}


void LevelEditor::reset()
{
	init();	
	m_lines.clear();
	m_colors.clear();
}


/////SETTER/////

void LevelEditor::setCurrentColor(const sf::Color &color)
{
	//Search for the inputcolor in the colorvector (getColorIndex)
	m_currentColor = getColorIndex(color);

	int counter = 0;

	for(std::size_t i = m_colors.size(); i > 0; i--)
	{
		if(i > 24)
			i = 24;

		m_displayLastColors[counter].setFillColor(m_colors[i-1]);
		counter++;
	}

}


void LevelEditor::setDrawingMode(DrawMode mode)
{
	m_drawMode = mode;
}

void LevelEditor::setSelectedScript(int index)
{
	int counter = 0;
	for(std::size_t i = 0; i < m_scriptManager.getSize(); i++)
	{
		if(m_scriptManager.getScript(i)->xPos == m_selectedXPos)
		{
			if(counter >= index)
			{
				m_selectedScript = m_scriptManager.getScript(i);
				return;
			}
			else
			{
				counter++;
			}

		}
	}
	m_selectedScript = nullptr;
}


/////GETTER/////

int LevelEditor::getSelectedXPos()
{
	return m_selectedXPos;
}

std::vector<std::string> LevelEditor::getScriptNames()
{
	std::vector<std::string> names;

	for(std::size_t i = 0; i < m_scriptManager.getSize(); i++)
	{
		if(m_scriptManager.getScript(i)->xPos == m_selectedXPos)
		{
			switch(m_scriptManager.getScript(i)->type)
			{
			case ScriptType::CHECKPOINT:
				names.push_back("Checkpoint");
				break;
			case ScriptType::CHANGE_SPEED:
				names.push_back("Change speed");
				break;
			case ScriptType::CHANGE_GRAVITATION:
				names.push_back("Change gravitation");
				break;
			case ScriptType::COLOR_INVERT:
				names.push_back("Color invert");
				break;
			case ScriptType::COLOR_OVERLAY:
				names.push_back("Color overlay");
				break;
			case ScriptType::FLICKERING:
				names.push_back("Flickering");
				break;
			case ScriptType::ROLL_CAMERA:
				names.push_back("Roll camera");
				break;
			case ScriptType::ZOOM:
				names.push_back("Zoom");
				break;
			default:
				names.push_back("No type selected");
			}
		}
	}

	return names;

}


Script *LevelEditor::getSelectedScript()
{
	return m_selectedScript;
}

const sf::Color &LevelEditor::getCurrentColor()
{
	return m_colors[m_currentColor];
}


/////PRIVATE/////

void LevelEditor::updateDisplay()
{
	for(std::size_t i = 0; i < m_display.size(); i++)
	{
		int col = i;

		while(col >= 32)
		{
			col -= 32;
		}
		
		int row = static_cast<int>(i/32.f);

		m_display[i].setFillColor(getColor(m_lines[m_xOffset + col].getColor(m_yOffset + row)));
	}

}


std::size_t LevelEditor::getColorIndex(const sf::Color &color)
{
	//Search for the color in the Array
	for(std::size_t i = 0; i < m_colors.size(); i++)
	{
		if(m_colors[i] == color)
			return i;
	}
	//If not already there save it into the vector and return the lasz element
	m_colors.push_back(color);
	return m_colors.size()-1;
}

const sf::Color &LevelEditor::getColor(int index)
{
	if(index >= 0 && index < m_colors.size())
	{
		return m_colors[index];
	}

	static sf::Color defaultColor = sf::Color(0,0,0);
	return defaultColor;
}

void LevelEditor::updateTexts()
{
	//Offset
	std::stringstream sstr;
	sstr << "Grid upper left corner: " << m_xOffset << " | " << m_yOffset;
	m_displayOffset.setString(sstr.str());
	
	sstr.str("");

	sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	int col = static_cast<int>(mousePos.x / 25.f);
	int row = static_cast<int>(mousePos.y / 25.f);

	if(col < 0)
		col = 0;
	else if(col > 31)
		col = 31;

	if(row < 0)
		row = 0;
	else if(row > 17)
		row = 17;

	sstr << "Mouse position: " << col + m_xOffset << " | " << row + m_yOffset;
	m_displayMousePos.setString(sstr.str());
}



void LevelEditor::save(std::fstream &file)
{
	file << "[Length]\n" << m_lines.size() << "\n";
	file << "///////////////////////////////////\n\n";
	file << "[Scripts]\n";
	
	for(std::size_t i = 0; i < m_scriptManager.getSize(); i++)
	{
		Script *temp = m_scriptManager.getScript(i);
		std::cout << temp->second << std::endl;
		file << temp->type << " " << temp->xPos << " " << static_cast<float>(temp->first) << " " << static_cast<float>(temp->second) << " " << static_cast<float>(temp->third) << "\n";
	}

	file << "[/Scripts]\n\n\n";

	file << "[Colors]\n";

	for (auto &it : m_colors)
	{
		file << static_cast<int>(it.r) << " " << static_cast<int>(it.g) << " " << static_cast<int>(it.b) << "\n";
	}

	file << "[/Colors]\n\n";


	file << "[Blocks]\n";

	for(auto &it : m_lines)
	{
		file << it.getStart() << " " << it.getEnd();
		for(std::size_t i = 0; i < it.getSize(); i++)
		{
			file << " " << it.getColor(i+it.getStart()) << " " << it.getCollisionType(i+it.getStart());
		}
		file << "\n";		
	}

	file << "[/Blocks]\n\n\n\n";
}


void LevelEditor::load(std::fstream &file)
{
	m_xOffset = 0;
	m_yOffset = 0;
}
