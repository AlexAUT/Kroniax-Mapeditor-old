#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP

#include <SFML/Graphics.hpp>
#include "enum.hpp"

class InputBox
{
public:
    InputBox(std::string name, int xPos, int yPos, int width, int height, sf::Color color, std::string text, sf::Font &font);

    void mouseEvents(sf::Vector2i mousePosition);
    void keyboardEvents(sf::Event event);

    //Getter
    std::string getName();
    std::string getText();

    //Setter
    void setPosition(sf::Vector2i position);
    void setSize(sf::Vector2i size);
    void moveButton(sf::Vector2i distance);

    void setFont(sf::Font &font);
    void setActive(bool state);
    void setDrawenable(bool state);
    void setOutlineThickness(int value);
    void setOutlineColor(sf::Color color);
    void setTextAlign(TextAlign value);
    void setText(std::string text);
    void setCharacterSize(int size);

    void draw(sf::RenderWindow &window);

private:
    void createBody();
    void createText();

private:
    std::string mName, mStringText;
    int mXPos, mYPos, mWidth, mHeight, mOutlineThickness;

    sf::Vertex mBody[4];
    sf::Vertex mOutline[4];
    sf::Vertex mUnselectedRect[4];
    sf::Text mText;

    sf::Color mBackgroundColors[2]; // 0=unactive, 1=active

    sf::Color mOutlineColor; // 0 = unselected, 1 = selected

    TextAlign mTextAlign;

    bool mActive, mSelected, mDraw;

};

#endif
