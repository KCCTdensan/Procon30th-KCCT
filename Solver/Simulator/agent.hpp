#pragma once

#include "../position.hpp"


namespace solver::simulator
{
	class Agent
	{
		const Size &fieldSize;
		TeamID team;
		Position position;

	public:
		Agent(const Size &fieldSize, TeamID team, Position initialPosition)noexcept
			: fieldSize(fieldSize), team(team), position(initialPosition)
		{

		}
		TeamID getTeam()const noexcept
		{
			return team;
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