#include <SFML/Graphics.hpp>

#include "../../include/AwGUI/layer.hpp"

#include "../../include/AwGUI/button.hpp"

Layer::Layer()
{
    mActive = false;
}

void Layer::addButton(std::string name, int xPos, int yPos, int width, int height, sf::Color top, sf::Color bottom, std::string caption, sf::Font &font)
{
    mButtons.push_back(Button(name, xPos, yPos, width, height, top, bottom, caption, font));
    mButtons[mButtons.size() - 1].setFont(font);
    mButtons[mButtons.size() - 1].setDrawenable(true);
}

void Layer::addInputBox(std::string name, int xPos, int yPos, int width, int height, sf::Color color, std::string text, sf::Font &font)
{
    mInputBoxes.push_back(InputBox(name, xPos, yPos, width, height, color, text, font));
}

void Layer::addPanel(std::string name, int xPos, int yPos, int width, int height, sf::Color color, int outlinethickenss)
{
    mPanels.push_back(Panel(name, xPos, yPos,  width, height, color, outlinethickenss));
}

void Layer::addDropDownMenu(std::string name, int xPos, int yPos, int width, int height, sf::Color top, sf::Color bottom, std::string caption, sf::Font &font)
{
    mDropDownMenus.push_back(DropDownMenu(name, xPos, yPos, width, height, top, bottom, caption, font));
    mDropDownMenus[mDropDownMenus.size() - 1].setFont(font);
    mDropDownMenus[mDropDownMenus.size() - 1].setDrawenable(true);
}

//Handlings
void Layer::mouseEvents(sf::Vector2i mousePosition)
{
    bool isDropMenuSelected = false; // IF True it will skip the Mouse Events for Buttons/INputBoxes, cause DropBoxes can overlay = strange action can happens

    for(unsigned int i = 0; i < mDropDownMenus.size(); i++)
    {
        mDropDownMenus[i].isMouseOver(mousePosition);
        mDropDownMenus[i].isClickedEvent();

        if(mDropDownMenus[i].getSelected())
        {
            isDropMenuSelected = true;
            break;
        }
    }

    if(isDropMenuSelected)
        return;  //Too skip the other parts

    //Buttons
    for(unsigned int i = 0; i < mButtons.size(); i++)
    {
        mButtons[i].isMouseOver(mousePosition);
        mButtons[i].isClickedEvent();
    }
    for(unsigned int i = 0; i < mInputBoxes.size(); i++)
    {
        mInputBoxes[i].mouseEvents(mousePosition);
    }
    for(unsigned int i = 0; i < mDropDownMenus.size(); i++)
    {
        mDropDownMenus[i].isMouseOver(mousePosition);
        mDropDownMenus[i].isClickedEvent();
    }
}

void Layer::keyboardEvents(sf::Event event)
{
    for(unsigned int i = 0; i < mInputBoxes.size(); i++)
    {
        mInputBoxes[i].keyboardEvents(event);
    }
}

//Getter
Button* Layer::getButton(std::string name)
{
    for(unsigned int i = 0; i < mButtons.size(); i++)
    {
        std::string temp;
        temp = mButtons[i].getName();

        if(temp == name)
            return &mButtons[i];
    }

    return nullptr;
}

InputBox* Layer::getInputBox(std::string name)
{
    for(unsigned int i = 0; i < mInputBoxes.size(); i++)
    {
        std::string temp;
        temp = mInputBoxes[i].getName();

        if(temp == name)
            return &mInputBoxes[i];
    }

    return nullptr;
}

Panel* Layer::getPanel(std::string name)
{
    for(unsigned int i = 0; i < mPanels.size(); i++)
    {
        std::string temp;
        temp = mPanels[i].getName();

        if(temp == name)
            return &mPanels[i];
    }

    return nullptr;
}

DropDownMenu* Layer::getDropDownMenu(std::string name)
{
    for(unsigned int i = 0; i < mDropDownMenus.size(); i++)
    {
        std::string temp;
        temp = mDropDownMenus[i].getName();

        if(temp == name)
            return &mDropDownMenus[i];
    }

    return nullptr;
}

//Setter
void Layer::setActive(bool value)
{
    mActive = value;
}

//Draw
void Layer::draw(sf::RenderWindow &window)
{
    if(mActive)
    {
        //Panels
        for(unsigned int i = 0; i < mPanels.size(); i++)
        {
            mPanels[i].draw(window);
        }
        //Buttons
        for(unsigned int i = 0; i < mButtons.size(); i++)
        {
            mButtons[i].draw(window);
        }
        //InputBoxes
        for(unsigned int i = 0; i < mInputBoxes.size(); i++)
        {
            mInputBoxes[i].draw(window);
        }

        int addressOfSelected = -1;

        for(unsigned int i = 0; i < mDropDownMenus.size(); i++)
        {
            if(mDropDownMenus[i].getSelected())
            {
                addressOfSelected = i;
                continue;
            }

            mDropDownMenus[i].draw(window);
        }

        if(addressOfSelected != -1)
            mDropDownMenus[addressOfSelected].draw(window);
    }
}
