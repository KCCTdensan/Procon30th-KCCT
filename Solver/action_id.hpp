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

	ActionID begin(ActionID)
	{
		return ActionID::stay;
	}

	ActionID end(ActionID)
	{
		return ActionID::numActionID;
	}

	ActionID operator*(ActionID action_id)
	{
		return action_id;
	}

	ActionID operator++(ActionID &action_id)
	{
		return action_id = static_cast<ActionID>(static_cast<int>(action_id) + 1);
	}
}