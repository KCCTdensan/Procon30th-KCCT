#pragma once

#include "basic.hpp"
#include "action_id.hpp"


class Direction
{
	char x;
	char y;

public:
	Direction(ActionID id)
	{
		switch(id)
		{
		case ID_TopLeft:
		case ID_Top:
		case ID_TopRight:
			y = -1;
			break;

		case ID_BottomLeft:
		case ID_Bottom:
		case ID_BottomRight:
			y = 1;
			break;

		default:
			y = 0;
			break;
		}
		switch(id)
		{
		case ID_TopLeft:
		case ID_Left:
		case ID_BottomLeft:
			x = -1;
			break;

		case ID_TopRight:
		case ID_Right:
		case ID_BottomRight:
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