#include "scriptManager.hpp"


ScriptManager::ScriptManager()
{

}

void ScriptManager::addScript(ScriptType type, int xPos, float first, float second, float third)
{
	m_scripts.push_back(Script(type, xPos));
	m_scripts.back().first = first;
	m_scripts.back().second = second;
	m_scripts.back().third = third;
}

void ScriptManager::addScript(const Script &script)
{
	m_scripts.push_back(script);
}


void ScriptManager::removeScript(std::size_t index)
{
	if(index < m_scripts.size())
	{
		m_scripts.erase(m_scripts.begin() + index);
	}
}

void ScriptManager::clear()
{
	m_scripts.clear();
}

std::size_t ScriptManager::getSize()
{
	return m_scripts.size();
}

Script *ScriptManager::getScript(std::size_t index)
{
	if(index < m_scripts.size())
	{
		return &m_scripts[index];
	}

	return nullptr;
}

bool ScriptManager::isScriptAtXPos(int xPos)
{
	for(auto &it : m_scripts)
	{
		if(it.xPos == xPos)
			return true;
	}
	return false;
}



