#include "AwGUI/gui.hpp"
#include "level.hpp"
#include "levelEditor.hpp"

#include "AwGUI/awMessageBox.hpp"
#include "utilities/converter.hpp"

#include <sstream>
#include "utilities/converter.hpp"

/////PROTOTYPES/////
void checkForGuiActions(AwGui &gui, Level &level);
	void layer0(AwGui &gui, Level &level);
		void updateLevelProperties(AwGui &gui, Level &level);

	void layer1(AwGui &gui, LevelEditor &levelEditor);
	void layer2(AwGui &gui, Level &level);
	void layer3(AwGui &gui, LevelEditor &levelEditor);
	void layer4(AwGui &gui, LevelEditor &levelEditor);
		void updateScriptInterface(AwGui &gui, LevelEditor &levelEditor);

	void updateGuiAfterLoading(AwGui &gui, Level &level);

/////IMPLEMENTATION/////

	void checkForGuiActions(AwGui &gui, Level &level)
{
	layer0(gui, level);
	layer1(gui, level.getLevelEditor());
	layer2(gui, level);
	layer3(gui, level.getLevelEditor());
	layer4(gui, level.getLevelEditor());
}

void layer0(AwGui &gui, Level &level)
{
	if(!gui.getLayerActive(0))
		return;

	if(gui.getButton(0, "new")->getClickState() == EventClickedType::released)
	{
		if(aw::MessageBoxYesNo("Creating new level", "Do you really want to create a new level?\n\nThe current level will be removed\nfrom the workspace"))
		{
			level.reset();
			level.createNewLevel();
		}
	}
	else if(gui.getButton(0, "save")->getClickState() == EventClickedType::released)
	{
		updateLevelProperties(gui, level);
		level.save();
	}
	else if(gui.getButton(0, "load")->getClickState() == EventClickedType::released)
	{
		if(aw::MessageBoxYesNo("Loading new level", "Do you really want to load a new level?\n\nThe current level will be removed\nfrom the workspace"))
		{
			level.reset();
			if(level.load(aw::MessageBoxInput("Insert level name", "Please insert the level's name you\n want to load", "")))
			{
				updateGuiAfterLoading(gui, level);
				aw::MessageBoxOK("Success", "Level loaded successfully!");
			}
			else
			{
				aw::MessageBoxOK("Error", "Failed to load the level!");
				level.reset();
				level.createNewLevel();
			}

		}
	}

	

}

void updateLevelProperties(AwGui &gui, Level &level)
{
	level.getProperties().name = gui.getInputBox(2, "name")->getText();
	level.getProperties().author = gui.getInputBox(2, "author")->getText();
	level.getProperties().startSpeed = gui.getInputBox(2, "startspeed")->getText();
	level.getProperties().startGravitation = gui.getInputBox(2, "startgravitation")->getText();
	level.getProperties().startPositionX = gui.getInputBox(2, "startpositionX")->getText();
	level.getProperties().startPositionY = gui.getInputBox(2, "startpositionY")->getText();
}



void layer1(AwGui &gui, LevelEditor &Leveleditor)
{
	if(!gui.getLayerActive(1))
		return;

	if(gui.getButton(1, "settings")->getClickState() == EventClickedType::released)
	{
		gui.setLayerActive(2, true);
		gui.setLayerActive(3, false);
		gui.setLayerActive(4, false);
		Leveleditor.setDrawingMode(DrawMode::nothing);
	}
	else if(gui.getButton(1, "design")->getClickState() == EventClickedType::released)
	{
		gui.setLayerActive(2, false);
		gui.setLayerActive(3, true);
		gui.setLayerActive(4, false);
		Leveleditor.setDrawingMode(DrawMode::opticalBlock);
		gui.getDropDownMenu(3, "mode")->setText("Optical block");
	}
	else if(gui.getButton(1, "scripts")->getClickState() == EventClickedType::released)
	{
		gui.setLayerActive(2, false);
		gui.setLayerActive(3, false);
		gui.setLayerActive(4, true);
		Leveleditor.setDrawingMode(DrawMode::scripts);
	}


}


void layer2(AwGui &gui, Level &level)
{
	if(!gui.getLayerActive(2))
		return;

	//Only update dropdownmenu, otherwise it wont work
	std::string selectedEntry = gui.getDropDownMenu(2, "difficulty")->getClickedEntryAsString();
	if(selectedEntry != "")
	{
		gui.getDropDownMenu(2, "difficulty")->setText(selectedEntry);
		level.getProperties().difficulty = selectedEntry;
	}

}

void layer3(AwGui &gui, LevelEditor &levelEditor)
{
	if(!gui.getLayerActive(3))
		return;

	switch(gui.getDropDownMenu(3, "mode")->getClickedEntryAsInt())
	{
	case 0: levelEditor.setDrawingMode(DrawMode::opticalBlock); break;
	case 1: levelEditor.setDrawingMode(DrawMode::collisionBlock); break;
	case 2: levelEditor.setDrawingMode(DrawMode::finishBlock); break;
	default: break;
	}

	if(gui.getButton(3, "applyColor")->getClickState() == EventClickedType::released)
	{
		std::stringstream sstr;
		sstr << gui.getInputBox(3, "r")->getText() << " " << gui.getInputBox(3, "g")->getText() << " " << gui.getInputBox(3, "b")->getText();
		int r, g, b;
		sstr >> r >> g >> b;
		levelEditor.setCurrentColor(sf::Color(r,g,b));
		
	}

	//update preview color
	std::stringstream sstr;
	sstr << gui.getInputBox(3, "r")->getText() << " " << gui.getInputBox(3, "g")->getText() << " " << gui.getInputBox(3, "b")->getText();
	int r, g, b;
	sstr >> r >> g >> b;
	gui.getButton(3, "currentColor")->setColor(sf::Color(r,g,b), sf::Color(r,g,b));

	//upate selected color
	gui.getButton(3, "selectedColor")->setColor(levelEditor.getCurrentColor(), levelEditor.getCurrentColor());
}

void layer4(AwGui &gui, LevelEditor &levelEditor)
{
	if(!gui.getLayerActive(4))
		return;

	//update selectedXPos text
	std::stringstream sstr;
	sstr << levelEditor.getSelectedXPos();
	gui.getInputBox(4, "selectedxpos")->setText(sstr.str());

	//update script dropdownmenu
	gui.getDropDownMenu(4, "selectScript")->clearEntries();
	std::vector<std::string> names = levelEditor.getScriptNames();
	for(auto &it : names)
	{
		gui.getDropDownMenu(4, "selectScript")->addEntry(it);
	}
	if(names.empty())
	{
		gui.getDropDownMenu(4, "selectScript")->setText("Select script");
	}



	//////////////////////////////////////////////////////////
	if(gui.getButton(4, "addScript")->getClickState() == EventClickedType::released)
	{
		levelEditor.addScript();
	}

	int selectedEntry = gui.getDropDownMenu(4, "selectScript")->getClickedEntryAsInt();
	if(selectedEntry >= 0)
	{
		levelEditor.setSelectedScript(selectedEntry);
		gui.getDropDownMenu(4, "selectScript")->setText(gui.getDropDownMenu(4, "selectScript")->getEntryName(selectedEntry));
		
		updateScriptInterface(gui, levelEditor);
	}

	//Type selection
	selectedEntry = gui.getDropDownMenu(4, "scriptType")->getClickedEntryAsInt();
	if(selectedEntry >= 0)
	{
		if(levelEditor.getSelectedScript())
		{
			switch(selectedEntry)
			{
			case 0: levelEditor.getSelectedScript()->type = ScriptType::CHECKPOINT; break;
			case 1: levelEditor.getSelectedScript()->type = ScriptType::CHANGE_SPEED; break;
			case 2: levelEditor.getSelectedScript()->type = ScriptType::CHANGE_GRAVITATION; break;
			case 3: levelEditor.getSelectedScript()->type = ScriptType::ROLL_CAMERA; break;
			case 4: levelEditor.getSelectedScript()->type = ScriptType::ZOOM; break;
			case 5: levelEditor.getSelectedScript()->type = ScriptType::FLICKERING; break;
			case 6: levelEditor.getSelectedScript()->type = ScriptType::COLOR_INVERT; break;
			case 7: levelEditor.getSelectedScript()->type = ScriptType::COLOR_OVERLAY; break;
			default: levelEditor.getSelectedScript()->type = ScriptType::NOTHING; break;
			}

			updateScriptInterface(gui, levelEditor);
		}
	}

	//Apply values
	if(gui.getButton(4, "saveValues")->getClickState() == EventClickedType::released)
	{
		if(levelEditor.getSelectedScript())
		{
			levelEditor.getSelectedScript()->first = aw::conv::ToFloat(gui.getInputBox(4, "scriptFirst")->getText());
			levelEditor.getSelectedScript()->second = aw::conv::ToFloat(gui.getInputBox(4, "scriptSecond")->getText());
			levelEditor.getSelectedScript()->third = aw::conv::ToFloat(gui.getInputBox(4, "scriptThird")->getText());
		}
	}
}


void updateScriptInterface(AwGui &gui, LevelEditor &levelEditor)
{
	if(!levelEditor.getSelectedScript())
		return;

	gui.getInputBox(4, "scriptFirst")->setText(std::string(aw::conv::ToString(levelEditor.getSelectedScript()->first)));
	gui.getInputBox(4, "scriptSecond")->setText(std::string(aw::conv::ToString(levelEditor.getSelectedScript()->second)));
	gui.getInputBox(4, "scriptThird")->setText(std::string(aw::conv::ToString(levelEditor.getSelectedScript()->third)));

	switch(levelEditor.getSelectedScript()->type)
	{
	case ScriptType::CHANGE_GRAVITATION:
		gui.getDropDownMenu(4, "selectScript")->setText("Change gravitation");
		gui.getDropDownMenu(4, "scriptType")->setText("Change gravitation");
		gui.getButton(4, "displayFirst")->setText("Value");
		gui.getButton(4, "displaySecond")->setText("Not used");
		gui.getButton(4, "displayThird")->setText("Not used");
		break;
	case ScriptType::CHANGE_SPEED:
		gui.getDropDownMenu(4, "selectScript")->setText("Change speed");
		gui.getDropDownMenu(4, "scriptType")->setText("Change speed");
		gui.getButton(4, "displayFirst")->setText("Value");
		gui.getButton(4, "displaySecond")->setText("Not used");
		gui.getButton(4, "displayThird")->setText("Not used");
		break;
	case ScriptType::CHECKPOINT:
		gui.getDropDownMenu(4, "selectScript")->setText("Checkpoint");
		gui.getDropDownMenu(4, "scriptType")->setText("Checkpoint");
		gui.getButton(4, "displayFirst")->setText("Not used");
		gui.getButton(4, "displaySecond")->setText("Not used");
		gui.getButton(4, "displayThird")->setText("Not used");
		break;
	case ScriptType::COLOR_INVERT:
		gui.getDropDownMenu(4, "selectScript")->setText("Color invert");
		gui.getDropDownMenu(4, "scriptType")->setText("Color invert");
		gui.getButton(4, "displayFirst")->setText("Not used");
		gui.getButton(4, "displaySecond")->setText("Not used");
		gui.getButton(4, "displayThird")->setText("Not used");
		break;
	case ScriptType::COLOR_OVERLAY:
		gui.getDropDownMenu(4, "selectScript")->setText("Color overlay");
		gui.getDropDownMenu(4, "scriptType")->setText("Color overlay");
		gui.getButton(4, "displayFirst")->setText("Red");
		gui.getButton(4, "displaySecond")->setText("Green");
		gui.getButton(4, "displayThird")->setText("Blue");
		break;
	case ScriptType::FLICKERING:
		gui.getDropDownMenu(4, "selectScript")->setText("Flickering");
		gui.getDropDownMenu(4, "scriptType")->setText("Flickering");
		gui.getButton(4, "displayFirst")->setText("Strength");
		gui.getButton(4, "displaySecond")->setText("Duration");
		gui.getButton(4, "displayThird")->setText("Not used");
		break;
	case ScriptType::ROLL_CAMERA:
		gui.getDropDownMenu(4, "selectScript")->setText("Roll camera");
		gui.getDropDownMenu(4, "scriptType")->setText("Roll camera");
		gui.getButton(4, "displayFirst")->setText("Not used");
		gui.getButton(4, "displaySecond")->setText("Not used");
		gui.getButton(4, "displayThird")->setText("Not used");
		break;
	case ScriptType::ZOOM:
		gui.getDropDownMenu(4, "selectScript")->setText("Zoom");
		gui.getDropDownMenu(4, "scriptType")->setText("Zoom");
		gui.getButton(4, "displayFirst")->setText("Factor");
		gui.getButton(4, "displaySecond")->setText("Not used");
		gui.getButton(4, "displayThird")->setText("Not used");
		break;
	default: 
		gui.getDropDownMenu(4, "scriptType")->setText("Select type");
		gui.getButton(4, "displayFirst")->setText("No type");
		gui.getButton(4, "displaySecond")->setText("No type");
		gui.getButton(4, "displayThird")->setText("No type");
		break;
	}
}


void updateGuiAfterLoading(AwGui &gui, Level &level)
{
	//Activate the settings layer
	gui.setLayerActive(2, true);
	gui.setLayerActive(3, false);
	gui.setLayerActive(4, false);
	level.getLevelEditor().setDrawingMode(DrawMode::nothing);
	//Update the settings layer inputboxes
	gui.getInputBox(2, "name")->setText(level.getProperties().name);
	gui.getInputBox(2, "author")->setText(level.getProperties().author);
	gui.getInputBox(2, "startspeed")->setText(level.getProperties().startSpeed);
	gui.getInputBox(2, "startgravitation")->setText(level.getProperties().startGravitation);
	gui.getInputBox(2, "startpositionX")->setText(level.getProperties().startPositionX);
	gui.getInputBox(2, "startpositionY")->setText(level.getProperties().startPositionY);
	gui.getDropDownMenu(2, "difficulty")->setText(level.getProperties().difficulty);
}
