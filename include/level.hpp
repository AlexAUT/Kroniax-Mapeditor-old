#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include "levelEditor.hpp"

struct Properties
{
	std::string name;
	std::string author;
	std::string difficulty;
	std::string startSpeed;
	std::string startGravitation;
	std::string startPositionX;
	std::string startPositionY;

	Properties():
		name(""),
		author("AlexAUT"),
		difficulty("Easy"),
		startSpeed("100"),
		startGravitation("75"),
		startPositionX("5"),
		startPositionY("5")
	{}
};


class Level
{
public:
	Level(sf::RenderWindow &window);

	void createNewLevel();
	void reset();

	bool load(const std::string &name);
	bool save();

	void keyInput(const sf::Event &event);
	void mouseInput();

	void render();

	/////GETTER/////
	LevelEditor &getLevelEditor();

	//For writing and reading!
	Properties &getProperties();

private:

private:
	sf::RenderWindow &m_window;

	Properties m_properties;

	LevelEditor m_levelEditor;
};


#endif