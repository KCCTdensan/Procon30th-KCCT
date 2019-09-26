#pragma once

#include "field.hpp"


class Agent
{
	const Field &field;
	Position position;

public:
	Agent(const Field &field, Position initialPosition)noexcept
		: field(field), position(initialPosition)
	{

	}
	Position getPosition()const noexcept
	{
		return position;
	}
	bool canMove(Direction direction)const noexcept
	{
		return position + direction <= field.getSize();
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