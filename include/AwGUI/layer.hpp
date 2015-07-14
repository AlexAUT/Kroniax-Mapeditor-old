#ifndef AwLayer_HPP
#define AwLayer_HPP

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "inputBox.hpp"
#include "panel.hpp"
#include "dropDownMenu.hpp"

class Layer
{
public:
    Layer();

    void addButton(std::string name, int xPos, int yPos, int width, int height, sf::Color top, sf::Color bottom, std::string caption, sf::Font &font);
    void addInputBox(std::string name, int xPos, int yPos, int width, int height, sf::Color color, std::string text, sf::Font &font);
    void addPanel(std::string name, int xPos, int yPos, int width, int height, sf::Color color, int outlinethickness);
    void addDropDownMenu(std::string name, int xPos, int yPos, int width, int height, sf::Color top, sf::Color bottom, std::string caption, sf::Font &font);
    //Handlings
    void mouseEvents(sf::Vector2i mousePosition);
    void keyboardEvents(sf::Event event);

    //Getter
    Button* getButton(std::string name);
    InputBox* getInputBox(std::string name);
    Panel* getPanel(std::string name);
    DropDownMenu* getDropDownMenu(std::string name);
    bool getActive(){return mActive;}
    //Setter
    void setActive(bool value);
    //Draw
    void draw(sf::RenderWindow &window);



private:
    bool mActive;

    sf::Font mFont;

    std::vector<Button> mButtons;
    std::vector<InputBox> mInputBoxes;
    std::vector<Panel> mPanels;
    std::vector<DropDownMenu> mDropDownMenus;

private:

};

#endif
