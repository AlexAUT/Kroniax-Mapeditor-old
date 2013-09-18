#include <SFML/Graphics.hpp>

#include "../../include/AwGUI/Button.hpp"

#include <iostream>


Button::Button(std::string name, int xPos, int yPos, int width, int height, sf::Color topColor, sf::Color bottomColor, std::string caption, sf::Font font)
{
    mName = name;
    mCaption = caption;

    mXPos =   xPos;
    mYPos =   yPos;
    mWidth =  width;
    mHeight = height;
    mBackgroundColors[0] = topColor;
    mBackgroundColors[1] = bottomColor;
    mBackgroundColors[2] = topColor;
    mBackgroundColors[3] = bottomColor;

    mOutlineColor = sf::Color(0,0,0);

    mActive = true;
    mDraw   = true;

    mOutline = 1;
	mText.setCharacterSize(15);
    mTextAlign = center;

    mText.setFont(font);

    createBody();
    createText();

    mClickState = nothing;
    mLaststate = false;
    mPressed = false;

	setMouseOverColors(bottomColor, topColor);
}


bool Button::isMouseOver(sf::Vector2i mousePosition)
{
    if(mActive && mousePosition.x >= mXPos && mousePosition.x <= (mXPos + mWidth) && mousePosition.y >= mYPos && mousePosition.y <= (mYPos + mHeight))
    {
        mIsMouseOver = true;
        return true;
    }else
    {
        mIsMouseOver = false;
        return false;
    }
}

EventClickedType Button::isClickedEvent()
{
    if(!mActive)
        return nothing;

    bool currentMouseState = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if(currentMouseState && mIsMouseOver)
    {
        if(mLaststate == false)
        {
            mPressed = true;
            mLaststate = currentMouseState;
            mClickState = pressed;
            return pressed;
        }
        if(mLaststate == true && mPressed)
        {
            mLaststate = currentMouseState;
            mText.setColor(sf::Color(255,0,0));
            mClickState = holding;
            return holding;
        }
    }
    if(!currentMouseState && mIsMouseOver && mPressed)
    {
        mPressed = false;
        mLaststate = currentMouseState;
        mClickState = released;
        return released;
    }

    mPressed = false;
    mLaststate = currentMouseState;
    mText.setColor(sf::Color(255,255,255));
    mClickState = nothing;
    return nothing;
}

//Setter
void Button::setPosition(sf::Vector2i position)
{
    int offsetOfTextX = mText.getPosition().x - mXPos;
    int offsetOfTextY = mText.getPosition().y - mYPos;

    mXPos = position.x;
    mYPos = position.y;

    createBody(); // new Body Position

    //new Text Position
    mText.setPosition(position.x + offsetOfTextX, position.y + offsetOfTextY);
}

void Button::setSize(sf::Vector2i size)
{
    mWidth = size.x;
    mHeight = size.y;

    createBody();
    createText();
}

void Button::moveButton(sf::Vector2i distance)
{
    mXPos += distance.x;
    mYPos += distance.y;

    createBody(); // new Body Position

    //new Text Position
    mText.setPosition(mText.getPosition().x + distance.x, mText.getPosition().y + distance.y);
}

void Button::setFont(sf::Font &font)
{
    mText.setFont(font);
}
void Button::setActive(bool state)
{
    mActive = state;
}

void Button::setDrawenable(bool state)
{
    mDraw = state;
}

void Button::setMouseOverColors(sf::Color topColor, sf::Color bottomColor)
{
    mBackgroundColors[2] = topColor;
    mBackgroundColors[3] = bottomColor;

    createBody();
}

void Button::setOutlineThickness(int value)
{
    mOutline = value;

    createBody();
}
void Button::setOutlineColor(sf::Color color)
{
    mOutlineColor = color;

    createBody();
}
void Button::setTextAlign(TextAlign value)
{
    mTextAlign = value;

    createText();
}
void Button::setText(std::string text)
{
    mCaption = text;
    createText();
}
void Button::setCharacterSize(int size)
{
    mText.setCharacterSize(size);

    createText();
}
void Button::setColor(sf::Color bottom, sf::Color top)
{
    mBackgroundColors[0] = bottom;
    mBackgroundColors[1] = top;

    createBody();
}

//Getter
sf::Vector2i Button::getPosition()
{
    return sf::Vector2i(mXPos, mYPos);
}

std::string Button::getName()
{
    return mName;
}

EventClickedType Button::getClickState()
{
    return mClickState;
}


void Button::draw(sf::RenderWindow &window)
{
    if(mDraw)
    {
        if(!mIsMouseOver)
        {
            window.draw(mVOutline, 4, sf::Quads);
            window.draw(mVBody,    4, sf::Quads);
        }else
        {
            window.draw(mVOutline,       4, sf::Quads);
            window.draw(mVBodyMouseOver, 4, sf::Quads);

        }
        window.draw(mText);
    }
}




//---------------------------------------------------------------------------------Private

void Button::createBody()
{
    //BodyNormal
    mVBody[0] = sf::Vertex(sf::Vector2f(mXPos + mOutline, mYPos + mHeight - mOutline), mBackgroundColors[1]);               // Left Bottom
    mVBody[1] = sf::Vertex(sf::Vector2f(mXPos + mOutline, mYPos + mOutline), mBackgroundColors[0]);                             // Left TOP
    mVBody[2] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutline, mYPos + mOutline), mBackgroundColors[0]);                //Right Top
    mVBody[3] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutline, mYPos + mHeight - mOutline), mBackgroundColors[1]);  //Right Bottom
    //BodyMouseover
    mVBodyMouseOver[0] = sf::Vertex(sf::Vector2f(mXPos + mOutline, mYPos + mHeight - mOutline), mBackgroundColors[3]);               // Left Bottom
    mVBodyMouseOver[1] = sf::Vertex(sf::Vector2f(mXPos + mOutline, mYPos + mOutline), mBackgroundColors[2]);                             // Left TOP
    mVBodyMouseOver[2] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutline, mYPos + mOutline), mBackgroundColors[2]);                //Right Top
    mVBodyMouseOver[3] = sf::Vertex(sf::Vector2f(mXPos + mWidth - mOutline, mYPos + mHeight - mOutline), mBackgroundColors[3]);  //Right Bottom
    //Outline
    mVOutline[0] = sf::Vertex(sf::Vector2f(mXPos, mYPos + mHeight), mOutlineColor); //Left Bottom
    mVOutline[1] = sf::Vertex(sf::Vector2f(mXPos, mYPos), mOutlineColor); //...
    mVOutline[2] = sf::Vertex(sf::Vector2f(mXPos + mWidth, mYPos), mOutlineColor);
    mVOutline[3] = sf::Vertex(sf::Vector2f(mXPos + mWidth, mYPos + mHeight), mOutlineColor);
}

void Button::createText()
{

    int xTextPos = 0;
    int yTextPos = 0;

    mText.setString("ABCDEFGHIJKLMNOPQRSTUVWXYZÜÖÄabcdefghijklmnopqrstuvwüöä");
    yTextPos = mYPos + static_cast<int>(mHeight / 2) - static_cast<int>(mText.getLocalBounds().height / 2);

    mText.setString(mCaption);

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


