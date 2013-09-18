#include "../../include/AwGUI/awMessageBox.hpp"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../../include/AwGUI/button.hpp"
#include "../../include/AwGUI/inputBox.hpp"

namespace aw
{
    bool MessageBoxYesNo(std::string title, std::string text)
    {
        sf::Font font;
        font.loadFromFile("data/fonts/DejaVuSans.ttf");

        bool yesOrNo = false;

        sf::RenderWindow window(sf::VideoMode(450,200,32), title, sf::Style::Default);

        sf::Text textDraw(text, font, 16);
        textDraw.setPosition(30,20);


        Button btYes("yes", 112, 140, 80, 40, sf::Color(20, 200, 30), sf::Color(20, 100, 30), "yes", font);
        btYes.setFont(font);
        btYes.setCharacterSize(18);
        btYes.setDrawenable(true);
        btYes.setMouseOverColors(sf::Color(20,100,30), sf::Color(20,200,30));

        Button btNo("no", 252, 140, 80, 40, sf::Color(200, 20, 30), sf::Color(100, 20, 30), "no", font);
        btNo.setFont(font);
        btNo.setCharacterSize(18);
        btNo.setDrawenable(true);
        btNo.setMouseOverColors(sf::Color(100,20,30), sf::Color(200,20,30));

        while(window.isOpen())
        {
            sf::Event e;

            while(window.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        break;
                    case sf::Event::Resized:
                        window.setSize(sf::Vector2u(100,50));
                        break;
                    default: break;
                }
            }

            btYes.isMouseOver(sf::Mouse::getPosition(window));
            btNo.isMouseOver(sf::Mouse::getPosition(window));

            btYes.isClickedEvent();
            btNo.isClickedEvent();

            if(btYes.getClickState() == released)
            {
                yesOrNo = true;
                window.close();
            }
            if(btNo.getClickState() == released)
            {
                yesOrNo = false;
                window.close();
            }

            window.clear(sf::Color(156,156,165));

            window.draw(textDraw);
            btYes.draw(window);
            btNo.draw(window);

            window.display();

        }

        return yesOrNo;
    }

    void MessageBoxOK(std::string title, std::string text)
    {
        sf::Font font;
        font.loadFromFile("data/fonts/DejaVuSans.ttf");

        sf::RenderWindow window(sf::VideoMode(300,150,32), title, sf::Style::Default);

        sf::Text textDraw(text, font, 16);
        textDraw.setPosition(30,20);

        Button btOK("ok", 110, 90, 80, 40, sf::Color(20, 200, 30), sf::Color(20, 100, 30), "ok", font);
        btOK.setFont(font);
        btOK.setCharacterSize(18);
        btOK.setDrawenable(true);
        btOK.setMouseOverColors(sf::Color(20,100,30), sf::Color(20,200,30));

        while(window.isOpen())
        {
            sf::Event e;

            while(window.pollEvent(e))
            {
                switch(e.type)
                {
                    case sf::Event::Closed:
                        break;
                    case sf::Event::Resized:
                        window.setSize(sf::Vector2u(100,50));
                        break;
                    default: break;
                }
            }

            btOK.isMouseOver(sf::Mouse::getPosition(window));

            btOK.isClickedEvent();

            if(btOK.getClickState() == released)
            {
                return;
            }


            window.clear(sf::Color(156,156,165));

            window.draw(textDraw);

            btOK.draw(window);

            window.display();

        }
    }

    std::string MessageBoxInput(std::string title, std::string text, std::string givenText)
    {
        sf::Font font;
        font.loadFromFile("data/fonts/DejaVuSans.ttf");

        std::string output = "";

        sf::RenderWindow window(sf::VideoMode(300,180,32), title, sf::Style::Default);

        sf::Text textDraw(text, font, 14);
        textDraw.setPosition(20,18);

        InputBox inp("text", 20, 75, 260, 25, sf::Color(222,222,222), givenText, font);
        inp.setCharacterSize(14);

        Button btYes("submit", 110, 120, 80, 40, sf::Color(20, 200, 30), sf::Color(20, 100, 30), "submit", font);
        btYes.setFont(font);
        btYes.setCharacterSize(18);
        btYes.setDrawenable(true);
        btYes.setMouseOverColors(sf::Color(20,100,30), sf::Color(20,200,30));


        while(window.isOpen())
        {
            sf::Event e;

            while(window.pollEvent(e))
            {
                inp.keyboardEvents(e);

                switch(e.type)
                {
                    case sf::Event::Closed:
                        break;
                    case sf::Event::Resized:
                        window.setSize(sf::Vector2u(100,50));
                        break;
                    default: break;
                }
            }

            btYes.isMouseOver(sf::Mouse::getPosition(window));

            btYes.isClickedEvent();

            inp.mouseEvents(sf::Mouse::getPosition(window));

            if(btYes.getClickState() == released)
            {
                output = inp.getText();
                window.close();
            }

            window.clear(sf::Color(156,156,165));

            window.draw(textDraw);
            btYes.draw(window);
            inp.draw(window);

            window.display();

        }

        return output;
    }



}
