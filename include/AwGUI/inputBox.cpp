#include <SFML/Graphics.hpp>

#include "../../include/AwGUI/inputBox.hpp"

#include <iostream>


InputBox::InputBox(std::string name, int xPos, int yPos, int width, int height, sf::Color color, std::string text, sf::Font &font)
{
    mName = name;
    mXPos = xPos;
    mYPos = yPos;
    mWidth = width;
    mHeight = height;
    mBackgroundColors[0] = color;
    mStringText = text;
    mText.setFont(font);
    mText.setColor(sf::Color::Black);
	mText.setCharacterSize(15);

    //Standardvalues
    mBackgroundColors[1] = sf::Color(156,156,156, 200);

    mOutlineThickness = 2;

    mTextAlign = left;

    mActive = true;
    mSelected = false;
    mDraw = true;


    createBody();
    createText();
}

void InputBox::mouseEvents(sf::Vector2i mousePosition)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(mActive && mousePosition.x >= mXPos && mousePosition.x <= (mXPos + mWidth) && mousePosition.y >= mYPos && mousePosition.y <= (mYPos + mHeight))
        {
            mSelected = true;
        }else
        {
            mSelected = false;
        }
    }
}



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Getter>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

std::string InputBox::getName()
{
    return mName;
}
std::string InputBox::getText()
{
    return mText.getString();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Setter >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InputBox::setPosition(sf::Vector2i position)
{
    int offsetOfTextX = mText.getPosition().x - mXPos;
    int offsetOfTextY = mText.getPosition().y - mYPos;

    mXPos = position.x;
    mYPos = position.y;

    createBody(); // new Body Position

    //new Text Position
    mText.setPosition(position.x + offsetOfTextX, position.y + offsetOfTextY);
}

void InputBox::setSize(sf::Vector2i size)
{
    mWidth = size.x;
    mHeight = size.y;

    createBody();
    createText();
}

void InputBox::moveButton(sf::Vector2i distance)
{
    mXPos += distance.x;
    mYPos += distance.y;

    createBody(); // new Body Position

    //new Text Position
    mText.setPosition(mText.getPosition().x + distance.x, mText.getPosition().y + distance.y);
}

void InputBox::setFont(sf::Font &font)
{
    mText.setFont(font);
}
void InputBox::setActive(bool state)
{
    mActive = state;
}

void InputBox::setDrawenable(bool state)
{
    mDraw = state;
}

void InputBox::setOutlineThickness(int value)
{
    mOutlineThickness = value;

    createBody();
}
void InputBox::setOutlineColor(sf::Color color)
{
    mOutlineColor = color;

    createBody();
}
void InputBox::setTextAlign(TextAlign value)
{
    mTextAlign = value;

    createText();
}
void InputBox::setText(std::string text)
{
    mStringText = text;
    createText();
}
void InputBox::setCharacterSize(int size)
{
    mText.setCharacterSize(size);

    createText();
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Draw >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void InputBox::draw(sf::RenderWindow &window)
{
    if(mDraw)
    {
        window.draw(mOutline, 4, sf::Quads);
        window.draw(mBody, 4, sf::Quads);

        if(!mSelected)
            window.draw(mUnselectedRect, 4, sf::Quads);

        window.draw(mText);
    }
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Private >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void InputBox::createBody()
{
    mBody[0] = sf::Vertex(sf::Vector2f(mXPos + mOutlineThickness, mYPos + mHeight - mOutlineThickness), mBackgroundColors[0]);               // Left Bottom
    mBody[1] = sf::Vertex(sf::Vector2f(mXPos + mOutlineThickness, mYPos + mOutlineThickness), mBackgroundColors[0]);                             // Left TOP
    mBody[2] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutlineThickness, mYPos + mOutlineThickness), mBackgroundColors[0]);                //Right Top
    mBody[3] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutlineThickness, mYPos + mHeight - mOutlineThickness), mBackgroundColors[0]);  //Right Bottom

    mOutline[0] = sf::Vertex(sf::Vector2f(mXPos, mYPos + mHeight), mOutlineColor); //Left Bottom
    mOutline[1] = sf::Vertex(sf::Vector2f(mXPos, mYPos),mOutlineColor); //...
    mOutline[2] = sf::Vertex(sf::Vector2f(mXPos + mWidth, mYPos), mOutlineColor);
    mOutline[3] = sf::Vertex(sf::Vector2f(mXPos + mWidth, mYPos + mHeight), mOutlineColor);

    mUnselectedRect[0] = sf::Vertex(sf::Vector2f(mXPos + mOutlineThickness, mYPos + mHeight - mOutlineThickness), mBackgroundColors[1]);               // Left Bottom
    mUnselectedRect[1] = sf::Vertex(sf::Vector2f(mXPos + mOutlineThickness, mYPos + mOutlineThickness), mBackgroundColors[1]);                             // Left TOP
    mUnselectedRect[2] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutlineThickness, mYPos + mOutlineThickness), mBackgroundColors[1]);                //Right Top
    mUnselectedRect[3] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutlineThickness, mYPos + mHeight - mOutlineThickness), mBackgroundColors[1]);  //Right Bottom

}

void InputBox::createText()
{
    int xTextPos = 0;
    int yTextPos = 0;

    mText.setString("ABCDEFGHIJKLMNOPQRSTUVWXYZÜÖÄabcdefghijklmnopqrstuvwüöä");
    yTextPos = mYPos + static_cast<int>(mHeight / 2) - static_cast<int>(mText.getLocalBounds().height / 2);

    mText.setString(mStringText);

    if(mTextAlign == center)
    {
        xTextPos = mXPos + static_cast<int>(mWidth / 2) - static_cast<int>(mText.getLocalBounds().width / 2);
    }
    if(mTextAlign == left)
    {
        xTextPos = mXPos + static_cast<int>(mWidth * 0.05);// 5 % right
    }
    if(mTextAlign == right)
    {
        xTextPos = mXPos + static_cast<int>((mWidth * 0.95)) - mText.getLocalBounds().width;// 5 % left
    }

    mText.setPosition(xTextPos, yTextPos);

}

void InputBox::keyboardEvents(sf::Event event)
{
    if(mSelected && mActive)
    {
        if (event.type == sf::Event::TextEntered)
        {
            sf::Uint32 unicode = event.text.unicode;
            // Ensure the unicode character is printable
            if (unicode > 30 && (unicode < 127 || unicode > 159))
            {
                sf::String string = mStringText;
                string += unicode;
                mStringText = string;
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
             //Delete
            if(event.key.code == sf::Keyboard::BackSpace)
            {
                if(mStringText.size() > 0)
                {
                    mStringText.erase(mStringText.size() - 1, 1);
                }
            }
        }

        createText();
    }
}
