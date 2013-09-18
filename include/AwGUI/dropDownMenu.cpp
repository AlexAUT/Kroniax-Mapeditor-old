#include <SFML/Graphics.hpp>

#include "../../include/AwGUI/dropDownMenu.hpp"

#include <iostream>


DropDownMenu::DropDownMenu(std::string name, int xPos, int yPos, int width, int height, sf::Color topColor, sf::Color bottomColor, std::string caption, sf::Font font)
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

    mOutline = 2;
    mTextAlign = left;

    mText.setFont(font);
	mText.setCharacterSize(15);

    createBody();
    createText();

    mClickState = nothing;
    mLaststate = false;
    mPressed = false;

    mSelectedEntry = -1;
    mCloseOneFrameBefore = false;
    mClapInAtClick = true;

    mEntryColor = sf::Color(170,170,170);
    mEntryMouseOverColor = sf::Color(100,100,100);
    mEntryOutlineColor = sf::Color(0,0,0);
    mEntryOutlineThickness = 1;

}

void DropDownMenu::addEntry(std::string entry)
{
    mEntries.push_back(entry);

    RecalculateVisualEntries();
}

void DropDownMenu::clearEntries()
{
	mEntries.clear();

	RecalculateVisualEntries();
}


bool DropDownMenu::isMouseOver(sf::Vector2i mousePosition)
{
    int currentHeight = mHeight; //Var too increase the Height if its selected!!

    if(mSelected && sf::Mouse::isButtonPressed(sf::Mouse::Left) && mSelectedEntry == -1)
    {
        mSelected = false;
        mCloseOneFrameBefore = true;
    }

    if(mSelected)
    {
        currentHeight = currentHeight * (mEntries.size()+1);
    }

    if(mActive && mousePosition.x >= mXPos && mousePosition.x <= (mXPos + mWidth) && mousePosition.y >= mYPos && mousePosition.y <= (mYPos + currentHeight))
    {
        mIsMouseOver = true;

        int counter = mEntries.size();

        while(mYPos + currentHeight > mousePosition.y)
        {
            counter--;
            currentHeight -= mHeight;
        }
        mSelectedEntry = counter;
        return true;
    }else
    {
        mIsMouseOver = false;
        if(mSelected)
            mSelected = false;
        return false;
    }
}

EventClickedType DropDownMenu::isClickedEvent()
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

        if(mCloseOneFrameBefore) // Open the Entrnies
            {
                mCloseOneFrameBefore = false;
        }else
        {
            mSelected = true;
        }

        return released;
    }

    mPressed = false;
    mLaststate = currentMouseState;
    mText.setColor(sf::Color(255,255,255));
    mClickState = nothing;

    return nothing;
}

//Setter
void DropDownMenu::setPosition(sf::Vector2i position)
{
    int offsetOfTextX = mText.getPosition().x - mXPos;
    int offsetOfTextY = mText.getPosition().y - mYPos;

    mXPos = position.x;
    mYPos = position.y;

    createBody(); // new Body Position

    //new Text Position
    mText.setPosition(position.x + offsetOfTextX, position.y + offsetOfTextY);
}

void DropDownMenu::setSize(sf::Vector2i size)
{
    mWidth = size.x;
    mHeight = size.y;

    createBody();
    createText();
}

void DropDownMenu::moveButton(sf::Vector2i distance)
{
    mXPos += distance.x;
    mYPos += distance.y;

    createBody(); // new Body Position

    //new Text Position
    mText.setPosition(mText.getPosition().x + distance.x, mText.getPosition().y + distance.y);
}

void DropDownMenu::setFont(sf::Font &font)
{
    mText.setFont(font);
}
void DropDownMenu::setActive(bool state)
{
    mActive = state;
}

void DropDownMenu::setDrawenable(bool state)
{
    mDraw = state;
}

void DropDownMenu::setMouseOverColors(sf::Color topColor, sf::Color bottomColor)
{
    mBackgroundColors[2] = topColor;
    mBackgroundColors[3] = bottomColor;

    createBody();
}

void DropDownMenu::setOutlineThickness(int value)
{
    mOutline = value;

    createBody();
}
void DropDownMenu::setOutlineColor(sf::Color color)
{
    mOutlineColor = color;

    createBody();
}
void DropDownMenu::setTextAlign(TextAlign value)
{
    mTextAlign = value;

    createText();
}
void DropDownMenu::setText(std::string text)
{
    mCaption = text;
    createText();
}
void DropDownMenu::setCharacterSize(int size)
{
    mText.setCharacterSize(size);

    createText();
}
void DropDownMenu::setColor(sf::Color bottom, sf::Color top)
{
    mBackgroundColors[0] = bottom;
    mBackgroundColors[1] = top;

    createBody();
}

void DropDownMenu::setEntryColor(sf::Color color)
{
    mEntryColor = color;
}
void DropDownMenu::setEntryOurlineColor(sf::Color color)
{
    mEntryOutlineColor = color;
}
void DropDownMenu::setEntryOutlineThickness(int value)
{
    mEntryOutlineThickness = value;
}
void DropDownMenu::setEntryMouseOverColor(sf::Color color)
{
    mEntryMouseOverColor = color;
}

//Getter
sf::Vector2i DropDownMenu::getPosition()
{
    return sf::Vector2i(mXPos, mYPos);
}

std::string DropDownMenu::getName()
{
    return mName;
}

EventClickedType DropDownMenu::getClickState()
{
    return mClickState;
}

int DropDownMenu::getClickedEntryAsInt()
{
    if(mSelected && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
       if(mClapInAtClick)
        {
            mSelected = false;
        }
        return mSelectedEntry;
    }
    return -1;
}

std::string DropDownMenu::getClickedEntryAsString()
{
    if(mSelected && sf::Mouse::isButtonPressed(sf::Mouse::Left) && mSelectedEntry >= 0 && mSelectedEntry < static_cast<int>(mEntries.size()))
    {
        if(mClapInAtClick)
        {
            mSelected = false;
        }
        return mEntries[mSelectedEntry];
    }
    return "";
}

std::string DropDownMenu::getEntryName(int index)
{
    if(index >= 0 && index < static_cast<int>(mEntries.size()))
        return mEntries[index];

    return "";
}
std::string DropDownMenu::getText()
{
    return mCaption;
}


void DropDownMenu::draw(sf::RenderWindow &window)
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
        window.draw(mTriangle, 3, sf::Triangles);

        if(mSelected)
        {
            sf::RectangleShape tempRect;
            tempRect.setSize(sf::Vector2f(mWidth, mHeight));
            tempRect.setFillColor(mEntryColor);
            tempRect.setOutlineThickness(mEntryOutlineThickness);
            tempRect.setOutlineColor(mEntryOutlineColor);

            static sf::Text tempEntryText = mText;
            tempEntryText.setColor(sf::Color::White);

            for(unsigned int i = 0; i < mEntries.size(); i++)
            {
                //Draw Rect Body
                tempRect.setPosition(mEntriesPosition[i]);

                if(mSelectedEntry == static_cast<int>(i))
                {
                    tempRect.setFillColor(mEntryMouseOverColor);

                    window.draw(tempRect);

                    tempRect.setFillColor(mEntryColor);
                }else
                {
                    window.draw(tempRect);
                }
                //Draw Text
                tempEntryText.setPosition(mEntriesTextPosition[i]);
                tempEntryText.setString(mEntries[i]);
                window.draw(tempEntryText);
            }
        }
    }
}




//---------------------------------------------------------------------------------Private

void DropDownMenu::createBody()
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

    //Triangle to show that it isnt a Button
    mTriangle[0] = sf::Vertex(sf::Vector2f(mXPos + (mWidth*0.85f), mYPos + (mHeight * 0.33f)), sf::Color(20,200,30)); //Left  upper corner
    mTriangle[1] = sf::Vertex(sf::Vector2f(mXPos + (mWidth*0.9f), mYPos + (mHeight * 0.66f)), sf::Color(20,200,30));  //Mid   down  corner
    mTriangle[2] = sf::Vertex(sf::Vector2f(mXPos + (mWidth*0.95f), mYPos + (mHeight * 0.33f)), sf::Color(20,200,30)); //Right upper corner
}

void DropDownMenu::createText()
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


void DropDownMenu::RecalculateVisualEntries()
{
    mEntriesPosition.clear();
    mEntriesTextPosition.clear();

    for(unsigned int i = 0; i < mEntries.size(); i++)
    {

        mEntriesPosition.push_back(sf::Vector2f(mXPos, mYPos + mHeight + (i * mHeight)));

        int tempYCoord = mEntriesPosition[i].y + static_cast<int>(mHeight / 2) - static_cast<int>(mText.getLocalBounds().height / 2);

        mEntriesTextPosition.push_back(sf::Vector2f(mXPos + (mWidth * 0.05), tempYCoord));

    }


}
