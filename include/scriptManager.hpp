#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include <vector>
#include <memory>

enum ScriptType
{
	NOTHING,
	CHECKPOINT,
	CHANGE_SPEED,
	CHANGE_GRAVITATION,
	ROLL_CAMERA,
	ZOOM,
	FLICKERING,
	COLOR_INVERT,
	COLOR_OVERLAY
};

struct Script 
{
	ScriptType type;
	int xPos;
    float first;
	float second;
	float third;

	Script(ScriptType pType, int pxPos) :
		type(pType), xPos(pxPos) {}
	Script(ScriptType pType, int pxPos, int pFirst, int pSecond, int pThird):
		type(pType), xPos(pxPos), first(pFirst), second(pSecond), third(pThird) {}
};


class ScriptManager 
{
public:
	ScriptManager();

	void addScript(ScriptType type, int xPos, float first, float second, float third);
	void addScript(const Script &script);

	void removeScript(std::size_t index);

	std::size_t getSize();
	Script *getScript(std::size_t index);

	bool isScriptAtXPos(int xPos);

private:

private:
	std::vector<Script> m_scripts;
};


#endif