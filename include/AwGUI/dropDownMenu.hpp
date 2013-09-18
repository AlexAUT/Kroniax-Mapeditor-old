#ifndef AwDROPDOWNMENU_HPP
#define AwDROPDOWNMENU_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "enum.hpp"

/*DropDownMenu Class

    Important: Width/Height includes the Outlinethickness!!! --> 200width + outlinethickness 50 = body 150px, outline 50px!

 */




class DropDownMenu
{
public:
    DropDownMenu(std::string name, int xPos, int yPos, int width, int height, sf::Color topColor, sf::Color bottomColor, std::string caption, sf::Font font);

    //ADD entries
    void addEntry(std::string text);
	void clearEntries();

    bool isMouseOver(sf::Vector2i mousePosition);
    EventClickedType isClickedEvent();

    //Setter
    void setPosition(sf::Vector2i position);
    void setSize(sf::Vector2i size);
    void moveButton(sf::Vector2i distance);

    void setFont(sf::Font &font);
    void setActive(bool state);
    void setDrawenable(bool state);
    void setMouseOverColors(sf::Color topColor, sf::Color bottomColor);
    void setOutlineThickness(int value);
    void setOutlineColor(sf::Color color);
    void setTextAlign(TextAlign value);
    void setText(std::string text);
    void setCharacterSize(int size);
    void setColor(sf::Color bottom, sf::Color top);
    void setEntryColor(sf::Color color);
    void setEntryOurlineColor(sf::Color color);
    void setEntryOutlineThickness(int value);
    void setEntryMouseOverColor(sf::Color color);
    void setClapInWhenClicking(bool value){mClapInAtClick = value;}

    void setSelected(bool value){mSelected = value;}
    //Getter
    sf::Vector2i getPosition();
    std::string getName();
    EventClickedType getClickState();
    int getClickedEntryAsInt();
    std::string getClickedEntryAsString();
    bool getSelected(){return mSelected;}
    std::string getEntryName(int index);
    std::string getText();

    //Draw
    void draw(sf::RenderWindow &window);

private:
    void createBody();
    void createText();

    void RecalculateVisualEntries();

private:
    std::string mName, mCaption;
    TextAlign mTextAlign;
    int mXPos, mYPos, mWidth, mHeight, mOutline;
    sf::Color mBackgroundColors[4]; // 0= normalTOP, 1=normalBottom, 2=mouseoverTop, 3=mouseoverBottom
    sf::Color mOutlineColor;
    sf::Color mEntryColor;
    sf::Color mEntryOutlineColor;
    sf::Color mEntryMouseOverColor;

    int mEntryOutlineThickness;

    sf::Vertex mVBody[4]; // 0-3Normal, 4-7 Mouseover
    sf::Vertex mVBodyMouseOver[4];
    sf::Vertex mVOutline[4];
    sf::Vertex mTriangle[3];

    sf::Text mText;
    std::vector<std::string> mEntries;
    std::vector<sf::Vector2f> mEntriesPosition;
    std::vector<sf::Vector2f> mEntriesTextPosition;

    bool mSelected;
    int mSelectedEntry;

    bool mCloseOneFrameBefore; // Need to not reopen when try to close....
    bool mClapInAtClick;

    bool mDraw;
    bool mActive;

    bool mIsMouseOver;
    bool mIsClicked;

    bool mLaststate;
    bool mPressed;

    EventClickedType mClickState;

};

#endif

