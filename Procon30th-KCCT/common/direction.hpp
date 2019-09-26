#pragma once

#include "basic.hpp"
#include "action_id.hpp"


class Direction
{
	int8_t x;
	int8_t y;

public:
	Direction(ActionID id)noexcept
	{
		switch(id)
		{
		case ActionID::ID_TopLeft:
		case ActionID::ID_Top:
		case ActionID::ID_TopRight:
			y = -1;
			break;

		case ActionID::ID_BottomLeft:
		case ActionID::ID_Bottom:
		case ActionID::ID_BottomRight:
			y = 1;
			break;

		default:
			y = 0;
			break;
		}
		switch(id)
		{
		case ActionID::ID_TopLeft:
		case ActionID::ID_Left:
		case ActionID::ID_BottomLeft:
			x = -1;
			break;

		case ActionID::ID_TopRight:
		case ActionID::ID_Right:
		case ActionID::ID_BottomRight:
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