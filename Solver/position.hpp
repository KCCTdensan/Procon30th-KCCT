#pragma once

#include "direction.hpp"
#include "size.hpp"


namespace solver
{
	struct Position
	{
		int8_t x;
		int8_t y;
		Position &move(const Direction &direction)noexcept
		{
			x += direction.getX();
			y += direction.getY();
			return *this;
		}
	};

	inline bool operator==(const Position &position1, const Position &position2)noexcept
	{
		return position1.x == position2.x && position1.y == position2.y;
	}

	inline bool operator!=(const Position &position1, const Position &position2)noexcept
	{
		return !(position1 == position2);
	}

	inline Position movedPosition(const Position &position, const Direction &direction)noexcept
	{
		return Position(position).move(direction);
	}

	inline bool isPositionInField(const Position &position, const Size &size)noexcept
	{
		return position.x >= 0 && position.x < size.width && position.y >= 0 && position.y < size.height;
	}
}