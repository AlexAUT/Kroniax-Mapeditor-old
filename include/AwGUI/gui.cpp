#include <SFML/Graphics.hpp>

#include "../../include/AwGUI/gui.hpp"

#include "../../include/AwGUI/layer.hpp"
#include "../../include/AwGUI/button.hpp"

AwGui::AwGui()
{

}

AwGui::AwGui(const std::string &fontPath)
{
	mFont.loadFromFile(fontPath);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Create Gui>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void AwGui::addLayer()
{
    mLayer.push_back(Layer());
}

void AwGui::setLayerActive(unsigned int index, bool value)
{
    if(index < mLayer.size())
        mLayer[index].setActive(value);
}

void AwGui::addButton(unsigned int layer, std::string name, int xPos, int yPos, int width, int height, sf::Color top, sf::Color bottom, std::string caption)
{
    mLayer[layer].addButton(name, xPos, yPos, width, height, top, bottom, caption, mFont);
}
void AwGui::addInputBox(unsigned int layer, std::string name, int xPos, int yPos, int width, int height, sf::Color color, std::string text)
{
    mLayer[layer].addInputBox(name, xPos, yPos, width, height, color, text, mFont);
}
void AwGui::addPanel(unsigned int layer, std::string name, int xPos, int yPos, int width, int height, sf::Color color, int outlineThickness)
{
    mLayer[layer].addPanel(name, xPos, yPos, width, height, color, outlineThickness);
}
void AwGui::addDropDownMenu(unsigned int layer, std::string name, int xPos, int yPos, int width, int height, sf::Color top, sf::Color bottom, std::string caption)
{
    mLayer[layer].addDropDownMenu(name, xPos, yPos, width, height, top, bottom, caption, mFont);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Manage Handlings >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void AwGui::mouseEvents(sf::Vector2i mousePosition)
{
    //Buttons
    for(unsigned int i = 0; i < mLayer.size(); i++)
    {
        if(mLayer[i].getActive())
            mLayer[i].mouseEvents(mousePosition);
    }
}

void AwGui::keyBoardEvents(sf::Event event)
{
    for(unsigned int i = 0; i < mLayer.size(); i++)
    {
        if(mLayer[i].getActive())
            mLayer[i].keyboardEvents(event);
    }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Getter>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

Button* AwGui::getButton(unsigned int layerIndex, std::string name)
{
    if(layerIndex < mLayer.size())
        return mLayer[layerIndex].getButton(name);

    return nullptr;
}

InputBox* AwGui::getInputBox(unsigned int layerIndex, std::string name)
{
    if(layerIndex < mLayer.size())
        return mLayer[layerIndex].getInputBox(name);

    return nullptr;
}

DropDownMenu* AwGui::getDropDownMenu(unsigned int layerIndex, std::string name)
{
    if(layerIndex < mLayer.size())
        return mLayer[layerIndex].getDropDownMenu(name);

    return nullptr;
}

bool AwGui::getLayerActive(std::size_t index)
{
	if(index < mLayer.size())
	{
		return mLayer[index].getActive();
	}

	return false;
}


void AwGui::setFont(sf::Font font)
{
    mFont = font;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Draw >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void AwGui::draw(sf::RenderWindow &window)
{

    for(unsigned int i = 0; i < mLayer.size(); i++)
    {
        mLayer[i].draw(window);
    }
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Private>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
