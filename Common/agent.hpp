#pragma once

#include "field.hpp"


class Agent
{
	const Field &field;
	Position position;

public:
	Agent(const Field &field, Position position)noexcept
		: field(field), position(position)
	{

	}
	Position getPosition()const noexcept
	{
		return position;
	}
	bool canMove(Direction direction)const noexcept
	{
		Position nextPosition = position + direction;
		return nextPosition.x >= 0 && nextPosition.x < field.getSize().width && nextPosition.y >= 0 && nextPosition.y < field.getSize().height;
	}
	void move(Direction direction)noexcept
	{
		if(!canMove(direction))
		{
			return;
		}
		position += direction;
	}
};