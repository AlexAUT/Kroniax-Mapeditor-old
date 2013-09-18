#include "../../include/AwGUI/panel.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

Panel::Panel(std::string name) //FAil name
{
    mName = name;
}

Panel::Panel(std::string name, int xPos, int yPos, int width, int height, sf::Color color, int outlineThickness)
{
    mName = name;
    mXPos = xPos;
    mYPos = yPos;
    mWidth= width;
    mHeight=height;

    mColor= color;
    mOutlineThickness = outlineThickness;

    mDraw = true;

    createBody();
}

std::string Panel::getName()
{
    return mName;
}

void Panel::draw(sf::RenderWindow &window)
{

     if(mDraw)
     {
         window.draw(mOutlines, 4, sf::Quads);
         window.draw(mBody, 4, sf::Quads);
     }
}



void Panel::createBody()
{
    mBody[0] = sf::Vertex(sf::Vector2f(mXPos, mYPos + mHeight - mOutlineThickness), mColor); //Left Bottom
    mBody[1] = sf::Vertex(sf::Vector2f(mXPos, mYPos), mColor); //Left Top
    mBody[2] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutlineThickness, mYPos), mColor); //...
    mBody[3] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutlineThickness, mYPos + mHeight - mOutlineThickness), mColor);

    mOutlines[0] = sf::Vertex(sf::Vector2f(mXPos, mYPos + mHeight), sf::Color::Black);
    mOutlines[1] = sf::Vertex(sf::Vector2f(mXPos, mYPos), sf::Color::Black);
    mOutlines[2] = sf::Vertex(sf::Vector2f(mXPos + mWidth, mYPos), sf::Color::Black);
    mOutlines[3] = sf::Vertex(sf::Vector2f(mXPos + mWidth, mYPos + mHeight), sf::Color::Black);
}


