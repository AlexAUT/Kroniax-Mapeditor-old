#ifndef LEVELEDITOR_HPP
#define LEVELEDITOR_HPP

//This class manage the display and change of the level...

/////INCLUDES/////
#include <iostream>
#include <array>
#include <vector>
#include <fstream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "levelLine.hpp"
#include "scriptManager.hpp"

/////FORWARD DECLARATION/////
namespace sf
{
	class RenderWindow;
	class Event;
}

/////STRUCTS/////
enum class DrawMode
{
	nothing, opticalBlock, collisionBlock, finishBlock, scripts
};



class LevelEditor 
{
public:
	LevelEditor(sf::RenderWindow &window);

	void keyInput(const sf::Event &event);
	void mouseInput();

	void render();

	void addScript();
	void addScript(const Script &script);

	void addLevelLine();
	void addBlockToLastLine(int yPos, int color, CollisionType type);

	void addColor(const sf::Color &color);

	void reset();

	/////SETTER/////
	void setCurrentColor(const sf::Color &color);
	void setDrawingMode(DrawMode mode);

	void setSelectedScript(int index);

	/////GETTER/////
	int getSelectedXPos();
	const sf::Color &getColor(int index);

	std::vector<std::string> getScriptNames();
	Script *getSelectedScript();

	const sf::Color &getCurrentColor();

	void save(std::fstream &file);
	void load(std::fstream &file);

private:

	void init();

	void updateDisplay();
	void updateTexts();

	std::size_t getColorIndex(const sf::Color &color);

private:
	sf::RenderWindow &m_window;

	std::array<sf::RectangleShape, 576> m_display;

	std::vector<sf::Color> m_colors;
	std::size_t m_currentColor;
	std::array<sf::RectangleShape, 25> m_displayLastColors;

	std::vector<LevelLine> m_lines;

	int m_xOffset;
	int m_yOffset;

	DrawMode m_drawMode;

	sf::Font m_font;
	sf::Text m_displayOffset;
	sf::Text m_displayMousePos;


	ScriptManager m_scriptManager;
	int m_selectedXPos; //Script position
	Script *m_selectedScript;
};



#endif