#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "include/AwGUI/gui.hpp"

#include "include/initGui.hpp"
#include "include/guiActions.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200,600), "Kroniax Map Editor");
	window.setVerticalSyncEnabled(true);
	bool hasFocus = true;

	AwGui gui("data/fonts/DejaVuSans.ttf");
	initGui(gui); // initGui.hpp

	Level level(window);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			gui.keyBoardEvents(event);
			level.keyInput(event);

			if(event.type == sf::Event::Closed)
				window.close();
			
			if(event.type == sf::Event::LostFocus)
				hasFocus = false;

			if(event.type == sf::Event::GainedFocus)
				hasFocus = true;
		}
		if(hasFocus)
		{
			gui.mouseEvents(static_cast<sf::Vector2i>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
			level.mouseInput();

			checkForGuiActions(gui, level); // guiActions.hpp

			window.clear(sf::Color(20,20,164));

			gui.draw(window);

			level.render();

			window.display();
		}
	}



	return 0;
}