#pragma once

#include "direction.hpp"
#include "size.hpp"


namespace solver
{
	struct Position
	{
		int x;
		int y;
		Position operator+=(Direction direction)
		{
			x += direction.getX();
			y += direction.getY();
			return *this;
		}
	};

	Position operator+(Position position, Direction direction)
	{
		return Position(position) += direction;
	}

	bool operator<=(Position position, Size size)
	{
		return position.x >= 0 && position.x < size.width && position.y >= 0 && position.y < size.height;
	}

	bool operator>(Position position, Size size)
	{
		return !(position <= size);
	}

	bool operator>=(Size size, Position position)
	{
		return position.x >= 0 && position.x < size.width && position.y >= 0 && position.y < size.height;
	}

	bool operator<(Size size, Position position)
	{
		return !(size >= position);
	}

	bool operator==(Position position1, Position position2)
	{
		return position1.x == position2.x && position1.y == position2.y;
	}

	bool operator!=(Position position1, Position position2)
	{
		return !(position1 == position2);
	}
}