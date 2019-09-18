#pragma once

#include "direction.hpp"


struct Position
{
	uchar x;
	uchar y;
	Position operator+=(Direction direction)
	{
		x += direction.getX();
		y += direction.getY();
		return *this;
	}
	//Position operator+=(ActionID);
};

Position operator+(Position position, Direction direction)
{
	return Position(position) += direction;
}

//Position operator+(Position, ActionID);

bool operator==(Position position1, Position position2)
{
	return position1.x == position2.x && position1.y == position2.y;
}

bool operator!=(Position position1, Position position2)
{
	return !(position1 == position2);
}