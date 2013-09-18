#include "levelLine.hpp"

#include <iostream>


LevelLine::LevelLine():
	m_start(100000), m_end(100000)
{

}



void LevelLine::addColor(std::size_t yPos, int color)
{
	if(m_blocks.size() == 0)
	{
		m_blocks.push_back(Block(color));
		m_start = yPos;
		m_end = yPos;
	}
	else if(yPos < m_start)
	{
		for(std::size_t i = yPos; i < m_start-1; i++)
		{
			m_blocks.push_front(Block());
		}
		m_blocks.push_front(Block(color));
		m_start = yPos;
	}
	else if(yPos > m_end)
	{
		for(std::size_t i = m_end; i < yPos - 1; i++)
		{
			m_blocks.push_back(Block());
		}
		m_blocks.push_back(Block(color));
		m_end = yPos;
	}
	else
	{
		m_blocks[yPos - m_start].color = color;
	}
}

void LevelLine::addCollisionType(std::size_t yPos, CollisionType type)
{
	if(m_blocks.size() == 0)
	{
		m_blocks.push_back(Block(type));
		m_start = yPos;
		m_end = yPos;
	}
	else if(yPos < m_start)
	{
		for(std::size_t i = yPos; i < m_start-1; i++)
		{
			m_blocks.push_front(Block());
		}
		m_blocks.push_front(Block(type));
		m_start = yPos;
	}
	else if(yPos > m_end)
	{
		for(std::size_t i = m_end; i < yPos - 1; i++)
		{
			m_blocks.push_back(Block());
		}
		m_blocks.push_back(Block(type));
		m_end = yPos;
	}
	else
	{
		m_blocks[yPos - m_start].collisionType = type;
	}
}



/////GETTER/////
std::size_t LevelLine::getStart()
{
	return m_start;
}
std::size_t LevelLine::getEnd()
{
	return m_end;
}
std::size_t LevelLine::getSize()
{
	return m_blocks.size();
}
int LevelLine::getColor(std::size_t index)
{
	if(index < m_start || index > m_end)
		return -1;

	return m_blocks[index - m_start].color;
}
CollisionType LevelLine::getCollisionType(std::size_t index)
{
	if(index < m_start || index > m_end)
		return CollisionType::NONE;

	return m_blocks[index - m_start].collisionType;
}


