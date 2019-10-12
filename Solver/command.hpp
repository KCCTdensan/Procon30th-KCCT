#pragma once

#include "direction.hpp"


namespace solver
{
	enum class ActionID
	{
		doNothing,
		setTileOnPanel,
		removePanel
	};

	constexpr size_t numActionID = 3;

	enum class CommandID
	{
		stay,
		setTopLeft,
		setTop,
		setTopRight,
		setLeft,
		setRight,
		setBottomLeft,
		setBottom,
		setBottomRight,
		removeTopLeft,
		removeTop,
		removeTopRight,
		removeLeft,
		removeRight,
		removeBottomLeft,
		removeBottom,
		removeBottomRight,
		null = -1
	};

	constexpr size_t numCommandID = 17;

	struct Command
	{
		DirectionID direction;
		ActionID action;

		Command(CommandID operationID)noexcept
		{
			switch(operationID)
			{
			case CommandID::setTopLeft:
				direction = DirectionID::topLeft;
				action = ActionID::setTileOnPanel;
				return;
			case CommandID::setTop:
				direction = DirectionID::top;
				action = ActionID::setTileOnPanel;
				return;
			case CommandID::setTopRight:
				direction = DirectionID::topRight;
				action = ActionID::setTileOnPanel;
				return;
			case CommandID::setLeft:
				direction = DirectionID::left;
				action = ActionID::setTileOnPanel;
				return;
			case CommandID::setRight:
				direction = DirectionID::right;
				action = ActionID::setTileOnPanel;
				return;
			case CommandID::setBottomLeft:
				direction = DirectionID::bottomLeft;
				action = ActionID::setTileOnPanel;
				return;
			case CommandID::setBottom:
				direction = DirectionID::bottom;
				action = ActionID::setTileOnPanel;
				return;
			case CommandID::setBottomRight:
				direction = DirectionID::bottomRight;
				action = ActionID::setTileOnPanel;
				return;
			case CommandID::removeTopLeft:
				direction = DirectionID::topLeft;
				action = ActionID::removePanel;
				return;
			case CommandID::removeTop:
				direction = DirectionID::top;
				action = ActionID::removePanel;
				return;
			case CommandID::removeTopRight:
				direction = DirectionID::topRight;
				action = ActionID::removePanel;
				return;
			case CommandID::removeLeft:
				direction = DirectionID::left;
				action = ActionID::removePanel;
				return;
			case CommandID::removeRight:
				direction = DirectionID::right;
				action = ActionID::removePanel;
				return;
			case CommandID::removeBottomLeft:
				direction = DirectionID::bottomLeft;
				action = ActionID::removePanel;
				return;
			case CommandID::removeBottom:
				direction = DirectionID::bottom;
				action = ActionID::removePanel;
				return;
			case CommandID::removeBottomRight:
				direction = DirectionID::bottomRight;
				action = ActionID::removePanel;
				return;
			default:
				direction = DirectionID::center;
				action = ActionID::doNothing;
			}
		}
		operator CommandID()noexcept
		{
			switch(direction)
			{
			case DirectionID::topLeft:
				switch(action)
				{
				case ActionID::setTileOnPanel:
					return CommandID::setTopLeft;
				case ActionID::removePanel:
					return CommandID::removeTopLeft;
				default:
					return CommandID::stay;
				}
			case DirectionID::top:
				switch(action)
				{
				case ActionID::setTileOnPanel:
					return CommandID::setTop;
				case ActionID::removePanel:
					return CommandID::removeTop;
				default:
					return CommandID::stay;
				}
			case DirectionID::topRight:
				switch(action)
				{
				case ActionID::setTileOnPanel:
					return CommandID::setTopRight;
				case ActionID::removePanel:
					return CommandID::removeTopRight;
				default:
					return CommandID::stay;
				}
			case DirectionID::left:
				switch(action)
				{
				case ActionID::setTileOnPanel:
					return CommandID::setLeft;
				case ActionID::removePanel:
					return CommandID::removeLeft;
				default:
					return CommandID::stay;
				}
			case DirectionID::right:
				switch(action)
				{
				case ActionID::setTileOnPanel:
					return CommandID::setRight;
				case ActionID::removePanel:
					return CommandID::removeRight;
				default:
					return CommandID::stay;
				}
			case DirectionID::bottomLeft:
				switch(action)
				{
				case ActionID::setTileOnPanel:
					return CommandID::setBottomLeft;
				case ActionID::removePanel:
					return CommandID::removeBottomLeft;
				default:
					return CommandID::stay;
				}
			case DirectionID::bottom:
				switch(action)
				{
				case ActionID::setTileOnPanel:
					return CommandID::setBottom;
				case ActionID::removePanel:
					return CommandID::removeBottom;
				default:
					return CommandID::stay;
				}
			case DirectionID::bottomRight:
				switch(action)
				{
				case ActionID::setTileOnPanel:
					return CommandID::setBottomRight;
				case ActionID::removePanel:
					return CommandID::removeBottomRight;
				default:
					return CommandID::stay;
				}
			default:
				return CommandID::stay;
			}
		}
	};
}