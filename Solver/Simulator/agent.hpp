#pragma once

#include "../position.hpp"


namespace solver::simulator
{
	class Agent
	{
		const Size fieldSize;
		const TeamID team;
		const uint8_t number;
		Position position;

	public:
		Agent(const Size &fieldSize, TeamID team, uint8_t number, Position initialPosition)noexcept
			: fieldSize(fieldSize), team(team), number(number), position(initialPosition)
		{

		}
		TeamID getTeam()const noexcept
		{
			return team;
		}
		uint8_t getNo()const noexcept
		{
			return number;
		}
		Position getCurrentPosition()const noexcept
		{
			return position;
		}
		bool canMovePositionally(Direction direction)const noexcept
		{
			return isPositionInField(movedPosition(position, direction), fieldSize);
		}
		void move(Direction direction)noexcept
		{
			if(canMovePositionally(direction))
			{
				position.move(direction);
			}
		}
	};
}