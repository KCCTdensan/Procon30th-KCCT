#pragma once

#include "action_id.hpp"


namespace solver
{
	class Direction
	{
		int x;
		int y;

	public:
		Direction(ActionID id)noexcept
		{
			switch(id)
			{
			case ActionID::topLeft:
			case ActionID::top:
			case ActionID::topRight:
				y = -1;
				break;

			case ActionID::bottomLeft:
			case ActionID::bottom:
			case ActionID::bottomRight:
				y = 1;
				break;

			default:
				y = 0;
				break;
			}
			switch(id)
			{
			case ActionID::topLeft:
			case ActionID::left:
			case ActionID::bottomLeft:
				x = -1;
				break;

			case ActionID::topRight:
			case ActionID::right:
			case ActionID::bottomRight:
				x = 1;
				break;

			default:
				x = 0;
				break;
			}
		}
		char getX()const noexcept
		{
			return x;
		}
		char getY()const noexcept
		{
			return y;
		}
	};
}