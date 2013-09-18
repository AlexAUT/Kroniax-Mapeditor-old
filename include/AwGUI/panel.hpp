
#ifndef PANEL_HPP
#define PANEL_HPP

#include <SFML/Graphics.hpp>

class Panel
{
public:
    Panel(std::string name); // For Fail search
    Panel(std::string name, int xPos, int yPos, int width, int height, sf::Color color, int outlineThickness); // Width includes 1outline, same for height, right corner = outline

    std::string getName();

    void draw(sf::RenderWindow &window);

private:
    void createBody();

private:
    std::string mName;
    int mXPos, mYPos, mWidth, mHeight, mOutlineThickness;
    sf::Color mColor;

    sf::Vertex mBody[4];
    sf::Vertex mOutlines[4];

    bool mDraw;

};

#endif
