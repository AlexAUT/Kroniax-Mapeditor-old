#include "AwGUI/gui.hpp"


void initGui(AwGui &gui)
{
	//Add layers
	//0 = NEW|OPEN|SAVE
	gui.addLayer();
	gui.setLayerActive(0, true);
	//1 = SETTINGS|DESIGN|SCRIPTS
	gui.addLayer();
	gui.setLayerActive(1, true);
	//2 = SETTINGS frame
	gui.addLayer();
	//3 = DESIGN frame
	gui.addLayer();
	//4 = Script frame
	gui.addLayer();

	//Fill layer 0
	sf::Color topColor = sf::Color(105,105,105);
	sf::Color botColor = sf::Color(29,59,55);

	gui.addPanel(0, "", 800, 0, 400, 64, sf::Color(125,50,50), 4);

	gui.addButton(0, "new", 820, 10, 100, 35, topColor, botColor, "New"); 
	gui.addButton(0, "save", 950, 10, 100, 35, topColor, botColor, "Save");
	gui.addButton(0, "load", 1080, 10, 100, 35, topColor, botColor, "Load");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Fill layer1
	
	gui.addPanel(1, "", 800, 64, 400, 60, sf::Color(125,50,50), 4);

	gui.addButton(1, "settings", 820, 74, 100, 35, sf::Color(174,30,40), sf::Color(144,40,40), "Settings");
	gui.addButton(1, "design", 950, 74, 100, 35, sf::Color(40,174,30), sf::Color(40,144,40), "Design");
	gui.addButton(1, "scripts", 1080, 74, 100, 35, sf::Color(30,40,174), sf::Color(40,40,144), "Scripts");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Fill layer2

	gui.addPanel(2, "", 800, 124, 400, 476, sf::Color(125,50,50), 3);

	gui.addButton(2, "nd", 820, 150, 65, 35, topColor, botColor, "Name:");
	gui.getButton(2, "nd")->setActive(false);

	gui.addButton(2, "na", 820, 200, 75, 35, topColor, botColor, "Author:");
	gui.getButton(2, "na")->setActive(false);

	gui.addButton(2, "ndd", 820, 250, 100, 35, topColor, botColor, "Difficulty:");
	gui.getButton(2, "ndd")->setActive(false);

	gui.addButton(2, "ns", 820, 300, 125, 35, topColor, botColor, "Startspeed:");
	gui.getButton(2, "ns")->setActive(false);

	gui.addButton(2, "ng", 820, 350, 170, 35, topColor, botColor, "Startgravitation:");
	gui.getButton(2, "ng")->setActive(false);

	gui.addButton(2, "nss", 820, 400, 170, 35, topColor, botColor, "Startposition in tiles:");
	gui.getButton(2, "nss")->setActive(false);

	gui.addInputBox(2, "name", 895, 150, 200, 35, sf::Color::White, "");
	gui.addInputBox(2, "author", 905, 200, 200,35, sf::Color::White, "AlexAUT");
	gui.addInputBox(2, "startspeed", 955, 300, 100, 35, sf::Color::White, "100");
	gui.addInputBox(2, "startgravitation", 1000, 350, 100, 35, sf::Color::White, "75");
	gui.addInputBox(2, "startpositionX", 1000, 400, 80, 35, sf::Color::White, "5");
	gui.addInputBox(2, "startpositionY", 1100, 400, 80, 35, sf::Color::White, "5");

	gui.addDropDownMenu(2, "difficulty", 930, 250, 200, 35, sf::Color(164,164,164), sf::Color(164,164,164), "Easy");
	gui.getDropDownMenu(2, "difficulty")->addEntry("Easy");
	gui.getDropDownMenu(2, "difficulty")->addEntry("Medium");
	gui.getDropDownMenu(2, "difficulty")->addEntry("Hard");
	gui.getDropDownMenu(2, "difficulty")->addEntry("Insane");
	gui.getDropDownMenu(2, "difficulty")->addEntry("Crazy");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Fill layer3

	gui.addPanel(3, "", 800, 124, 400, 476, sf::Color(50,125,50), 3);

	gui.addButton(3, "sm", 820, 150, 125, 35, topColor, botColor, "Select mode:");
	gui.getButton(3, "sm")->setActive(false);
	gui.addDropDownMenu(3, "mode", 955, 150, 175, 35, sf::Color(164,164,164), sf::Color(164,164,164), "Visible block");
	gui.getDropDownMenu(3, "mode")->addEntry("Optical block");
	gui.getDropDownMenu(3, "mode")->addEntry("Collision block");
	gui.getDropDownMenu(3, "mode")->addEntry("Finish block");

	gui.addButton(3, "dc", 820, 250, 75, 35, topColor, botColor, "Color:");
	gui.getButton(3, "dc")->setActive(false);

	gui.addInputBox(3, "r", 915, 250, 50, 35, sf::Color::White, "255");
	gui.getInputBox(3, "r")->setTextAlign(TextAlign::center);
	gui.addInputBox(3, "g", 975, 250, 50, 35, sf::Color::White, "255");
	gui.getInputBox(3, "g")->setTextAlign(TextAlign::center);
	gui.addInputBox(3, "b", 1035, 250, 50, 35, sf::Color::White, "255");
	gui.getInputBox(3, "b")->setTextAlign(TextAlign::center);

	gui.addButton(3, "applyColor", 1100, 250, 80, 35, topColor, botColor, "Add Color");

	gui.addButton(3, "dcc", 820, 300, 130, 35, topColor, botColor, "Preview color: ");
	gui.getButton(3, "dcc")->setActive(false);

	gui.addButton(3, "currentColor", 960, 300, 35, 35, sf::Color::White, sf::Color::White, "");
	gui.getButton(3, "currentColor")->setActive(false);

	gui.addButton(3, "dcl", 820, 375, 120, 35, topColor, botColor, "Select color: ");
	gui.getButton(3, "dcl")->setActive(false);

	gui.addButton(3, "dscl", 820, 520, 120, 35, topColor, botColor, "Selected color:");
	gui.getButton(3, "dscl")->setActive(false);

	gui.addButton(3, "selectedColor", 950, 520, 35, 35, sf::Color::White, sf::Color::White, "");
	gui.getButton(3, "selectedColor")->setActive(false);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Fill layer4

	gui.addPanel(4, "", 800, 124, 400, 476, sf::Color(50,50,125), 3);

	gui.addButton(4, "ds", 820, 150, 180, 35, topColor, botColor, "Selected X Position:");
	gui.getButton(4, "ds")->setActive(false);
	gui.addInputBox(4, "selectedxpos", 1010, 150, 75, 35, sf::Color::White, "0");

	gui.addDropDownMenu(4, "selectScript", 820, 200, 210, 30, topColor, topColor, "Select script");

	gui.addButton(4, "addScript", 1050, 200, 75, 35, topColor, botColor, "Add");

	gui.addButton(4, "dt", 820, 300, 100, 35, topColor, botColor, "Type: ");
	gui.getButton(4, "dt")->setActive(false);

	gui.addDropDownMenu(4, "scriptType", 930, 300, 200, 30, topColor, topColor, "Select type");
	gui.getDropDownMenu(4, "scriptType")->addEntry("Checkpoint");
	gui.getDropDownMenu(4, "scriptType")->addEntry("Change speed");
	gui.getDropDownMenu(4, "scriptType")->addEntry("Change gravitation");
	gui.getDropDownMenu(4, "scriptType")->addEntry("Flip camera");
	gui.getDropDownMenu(4, "scriptType")->addEntry("Zoom");
	gui.getDropDownMenu(4, "scriptType")->addEntry("Flickering");
	gui.getDropDownMenu(4, "scriptType")->addEntry("Color invert");
	gui.getDropDownMenu(4, "scriptType")->addEntry("Color overlay");

	gui.addButton(4, "displayFirst", 820, 350, 100, 35, topColor, botColor, "First: ");
	gui.getButton(4, "displayFirst")->setActive(false);

	gui.addInputBox(4, "scriptFirst", 930, 350, 50, 35, sf::Color::White, "0");

	gui.addButton(4, "displaySecond", 820, 400, 100, 35, topColor, botColor, "Second: ");
	gui.getButton(4, "displaySecond")->setActive(false);

	gui.addInputBox(4, "scriptSecond", 930, 400, 50, 35, sf::Color::White, "0");

	gui.addButton(4, "displayThird", 820, 450, 100, 35, topColor, botColor, "Third: ");
	gui.getButton(4, "displayThird")->setActive(false);

	gui.addInputBox(4, "scriptThird", 930, 450, 50, 35, sf::Color::White, "0");

	gui.addButton(4, "saveValues", 1000, 350, 100, 135, topColor, botColor, "Save values");
}
