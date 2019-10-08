#pragma once

#include "../position.hpp"


namespace solver::simulator
{
	class Agent
	{
		const Size &fieldSize;
		Position position;

	public:
		Agent(const Size &fieldSize, Position initialPosition)noexcept
			: fieldSize(fieldSize), position(initialPosition)
		{

		}
		Position getPosition()const noexcept
		{
			return position;
		}
		bool canMove(Direction direction)const noexcept
		{
			return isPositionInField(movedPosition(position, direction), fieldSize);
		}
		void move(Direction direction)noexcept
		{
			if(!canMove(direction))
			{
				return;
			}
			position.move(direction);
		}
	};
}