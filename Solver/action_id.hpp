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
		numActionID,
		null = -1
	};

	inline ActionID begin(ActionID)
	{
		return ActionID::stay;
	}

	inline ActionID end(ActionID)
	{
		return ActionID::numActionID;
	}

	inline ActionID operator*(ActionID action_id)
	{
		return action_id;
	}

	inline ActionID operator++(ActionID &action_id)
	{
		return action_id = static_cast<ActionID>(static_cast<int>(action_id) + 1);
	}
}