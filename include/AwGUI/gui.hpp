#ifndef AWGUI_HPP
#define AWGUI_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "layer.hpp"

#include "button.hpp"
#include "inputBox.hpp"
#include "dropDownMenu.hpp"

class AwGui
{
public:
    AwGui();
    AwGui(const std::string &fontPath);

    //CreateGui

    void addLayer();

    void setLayerActive(unsigned int index, bool value);

    void addButton(unsigned int layer, std::string name, int xPos, int yPos, int width, int height, sf::Color top, sf::Color bottom, std::string caption);
    void addInputBox(unsigned int layer, std::string name, int xPos, int yPos, int width, int height, sf::Color color, std::string text);
    void addPanel(unsigned int layer, std::string name, int xPos, int yPos, int width, int height, sf::Color color, int outlineThickness);
    void addDropDownMenu(unsigned int layer, std::string name, int xPos, int yPos, int width, int height, sf::Color top, sf::Color bottom, std::string caption);

    //Manage Handlings
    void mouseEvents(sf::Vector2i mousePosition);
    void keyBoardEvents(sf::Event event);

    //Getter
    Button* getButton(unsigned int layerIndex, std::string name); // name isn´t caption
    InputBox* getInputBox(unsigned int layerIndex, std::string name);
    DropDownMenu* getDropDownMenu(unsigned int layerIndex, std::string name); // name isn´t caption

	bool getLayerActive(std::size_t index);

    void setFont(sf::Font font);

    //Draw
    void draw(sf::RenderWindow &window);

private:
    void MouseOver();//Call in draw();
private:
    std::vector<Layer> mLayer;

    sf::Font mFont;

private:

};

#endif
