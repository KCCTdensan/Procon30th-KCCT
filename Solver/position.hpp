#pragma once

#include "direction.hpp"
#include "size.hpp"


namespace solver
{
	struct Position
	{
		int8_t x;
		int8_t y;

		Position()
			: x(0), y(0)
		{

		}
		Position(int8_t x, int8_t y)
			: x(x), y(y)
		{

		}
		Position &move(const Direction &direction)noexcept
		{
			x += direction.getDx();
			y += direction.getDy();
			return *this;
		}
	};

	inline bool operator==(Position position1, Position position2)noexcept
	{
		return position1.x == position2.x && position1.y == position2.y;
	}

	inline bool operator!=(Position position1, Position position2)noexcept
	{
		return !(position1 == position2);
	}

	inline Position movedPosition(Position position, Direction direction)noexcept
	{
		return position.move(direction);
	}

	inline bool isPositionInField(Position position, Size size)noexcept
	{
		return position.x >= 0 && position.x < size.width && position.y >= 0 && position.y < size.height;
	}
}