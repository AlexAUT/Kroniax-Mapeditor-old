#include "level.hpp"

#include "AwGUI/awMessageBox.hpp"
#include "utilities/converter.hpp"

#include <fstream>
#include <sstream>

Level::Level(sf::RenderWindow &window) :
	m_window(window), m_levelEditor(window)
{

}

void Level::createNewLevel()
{
	reset();
	m_levelEditor.init();
}


void Level::reset()
{
	//Reset the level
	m_properties = Properties();
	m_levelEditor.reset();
}

bool Level::save()
{
	std::fstream file(("data/levels/"+m_properties.name+".cfg").c_str(), std::ios::out | std::ios::trunc);

	file << "////////////////////////////\nLevelfile for Kroniax\n////////////////////////////\n\n\n";
	file << "[Name]\n";
	file << m_properties.name << "\n";
	file << "[Author]\n";
	file << m_properties.author << "\n";
	file << "[Difficulty]\n";
	file << m_properties.difficulty << "\n";
	file << "[Start speed]\n";
	file << m_properties.startSpeed << "\n";
	file << "[Start Gravitation]\n";
	file << m_properties.startGravitation << "\n";
	
	m_levelEditor.save(file);

	file.close();
	return true;
}


bool Level::load(const std::string &name)
{
	std::fstream file(("data/levels/"+name+".cfg").c_str(), std::ios::in);

	if(file.fail())
	{
		return false;
	}

	std::string line;
	while(std::getline(file, line))
	{
		if(line == "[Name]")
		{
			std::string temp;
			std::getline(file, temp);
			m_properties.name = temp;
		}
		else if(line == "[Author]")
		{
			std::string temp;
			std::getline(file, temp);
			m_properties.author = temp;
		}
		else if(line == "[Difficulty]")
		{
			std::string temp;
			std::getline(file, temp);
			m_properties.difficulty = temp;
		}
		else if(line == "[Start speed]")
		{
			std::string temp;
			std::getline(file, temp);
			m_properties.startSpeed = temp;
		}
		else if(line == "[Start Gravitation]")
		{
			std::string temp;
			std::getline(file, temp);
			m_properties.startGravitation = temp;
		}
		else if(line == "[Scripts]")
		{
			while(std::getline(file, line))
			{
				if(line == "[/Scripts]")
				{
					break;
				}
				else
				{
					std::stringstream sstr(line);
					int type, xPos, first, second, third;
					sstr >> type >> xPos >> first >> second >> third;
					m_levelEditor.addScript(Script(ScriptType(type), xPos, first, second, third));
				}
			}
		}
		else if(line == "[Blocks]")
		{
			while(std::getline(file, line))
			{
				if(line == "[/Blocks]")
				{
					break;
				}
				else
				{
					m_levelEditor.addLevelLine();

					int start, end;
					std::stringstream sstr(line);
					sstr >> start >> end;

			
					if(start < 10000 && end < 10000)
					{
						for(std::size_t i = start; i <= end; i++)
						{
							int color, type;
							sstr >> color >> type;
							m_levelEditor.addBlockToLastLine(i, color, CollisionType(type));
						}
					}
				}

			}
		}
		else if(line == "[Colors]")
		{
			while(std::getline(file, line))
			{
				if(line == "[/Colors]")
				{
					break;
				}
				else
				{
					std::stringstream sstr(line);
					int r,g,b;
					sstr >> r >> g >> b;
					m_levelEditor.addColor(sf::Color(r,g,b));
				}
			}
			m_levelEditor.setCurrentColor(m_levelEditor.getColor(0));
		}


	}

	m_levelEditor.load(file);

	file.close();
	return true;
}


void Level::keyInput(const sf::Event &event)
{
	m_levelEditor.keyInput(event);
}

void Level::mouseInput()
{
	m_levelEditor.mouseInput();
}

void Level::render()
{
	m_levelEditor.render();
}





/////GETTER/////

Properties &Level::getProperties()
{
	return m_properties;
}


LevelEditor &Level::getLevelEditor()
{
	return m_levelEditor;
}
