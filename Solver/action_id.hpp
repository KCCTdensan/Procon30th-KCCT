#pragma once


namespace solver
{
	constexpr int numActionID = 9;

	enum class ActionID
	{
		stay,
		topLeft,
		top,
		topRight,
		left,
		right,
		bottomLeft,
		bottom,
		bottomRight,
		null = -1
	};
}