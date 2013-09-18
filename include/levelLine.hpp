#ifndef LEVELLINE_HPP
#define LEVELLINE_HPP

#include <deque>

#include <SFML/Graphics/Color.hpp>

/////ENUM/////
enum CollisionType
{
	NONE, COLLISION, FINISH
};
/////STRUCT/////
struct Block 
{
	/////MEMBERS/////
	int color;
	CollisionType collisionType;

	/////CONSTRUCTORS/////
	Block() : color(-1), collisionType(CollisionType::NONE) {}
	Block(int pcolor) : color(pcolor), collisionType(CollisionType::NONE) {}
	Block(CollisionType type) : color(-1), collisionType(type) {}
	Block(int pcolor, CollisionType type) : color(color), collisionType(type) {}
};


class LevelLine
{
public:

	LevelLine();

	void addColor(std::size_t yPos, int color);
	void addCollisionType(std::size_t yPos, CollisionType type);

	std::size_t getStart();
	std::size_t getEnd();
	std::size_t getSize();
	int getColor(std::size_t index);
	CollisionType getCollisionType(std::size_t index);

private:

private:
	std::size_t m_start;
	std::size_t m_end;

	std::deque<Block> m_blocks;
};


#endif