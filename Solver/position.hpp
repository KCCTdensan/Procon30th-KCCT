#pragma once

#include "direction.hpp"
#include "size.hpp"


namespace solver
{
	struct Position
	{
		int x;
		int y;
		Position &move(const Direction &direction)
		{
			x += direction.getX();
			y += direction.getY();
			return *this;
		}
	};

	bool operator==(const Position &position1, const Position &position2)
	{
		return position1.x == position2.x && position1.y == position2.y;
	}

	bool operator!=(const Position &position1, const Position &position2)
	{
		return !(position1 == position2);
	}

	Position movedPosition(const Position &position, const Direction &direction)
	{
		return Position(position).move(direction);
	}

	bool isPositionInField(const Position &position, const Size &size)
	{
		return position.x >= 0 && position.x < size.width && position.y >= 0 && position.y < size.height;
	}
}