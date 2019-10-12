#pragma once


namespace solver
{
	enum class DirectionID
	{
		topLeft,
		top,
		topRight,
		left,
		center,
		right,
		bottomLeft,
		bottom,
		bottomRight
	};

	constexpr size_t numDirectionID = 9;
	
	class Direction
	{
		int dx : 2;
		int dy : 2;

	public:
		Direction()noexcept
		{
			dx = 0;
			dy = 0;
		}
		Direction(DirectionID directionID)noexcept
		{
			switch(directionID)
			{
			case DirectionID::topLeft:
				dx = -1;
				dy = -1;
				return;
			case DirectionID::top:
				dx = 0;
				dy = -1;
				return;
			case DirectionID::topRight:
				dx = 1;
				dy = -1;
				return;
			case DirectionID::left:
				dx = -1;
				dy = 0;
				return;
			case DirectionID::right:
				dx = 1;
				dy = 0;
				return;
			case DirectionID::bottomLeft:
				dx = -1;
				dy = 1;
				return;
			case DirectionID::bottom:
				dx = 0;
				dy = 1;
				return;
			case DirectionID::bottomRight:
				dx = 1;
				dy = 1;
				return;
			default:
				dx = 0;
				dy = 0;
				return;
			}
		}
		char getDx()const noexcept
		{
			return dx;
		}
		char getDy()const noexcept
		{
			return dy;
		}
	};
}