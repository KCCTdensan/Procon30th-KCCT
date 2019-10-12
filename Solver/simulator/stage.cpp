#include "stage.hpp"


namespace solver::simulator
{
	void Stage::updatePanels(const StageCommand &command)
	{
		for(int t = 0; t < numTeams; ++t)
		{
			for(uint8_t i = 0; i < agentManager.getNumAgents(); ++i)
			{
				const TeamID team = static_cast<TeamID>(t);
				const Agent &agent = agentManager(team, i);
				const Command agentCommand = command.teamCommands[t].commands[i];
				const Direction direction = agentCommand.direction;
				const ActionID action = agentCommand.action;
				const Position nextPosition = movedPosition(agent.getCurrentPosition(), direction);
				switch(action)
				{
				case ActionID::setTileOnPanel:
					field.setTileOnPanel(nextPosition, toTile(team));
					break;

				case ActionID::removePanel:
					field.removeTileOnPanel(nextPosition);
					break;
				}
			}
		}
		scoreManager.update();
	}

	void Stage::moveAgents(const StageCommand &command)
	{
		std::array<std::vector<Direction>, numTeams> directions;
		for(int t = 0; t < numTeams; ++t)
		{
			size_t numAgents = agentManager.getNumAgents();
			directions[t].resize(numAgents);
			for(uint8_t i = 0; i < numAgents; ++i)
			{
				const Command agentCommand = command.teamCommands[t].commands[i];
				const ActionID action = agentCommand.action;
				directions[t][i] = action == ActionID::setTileOnPanel ? agentCommand.direction : DirectionID::center;
			}
		}
		agentManager.move(directions);
	}

	Stage::Stage(const Stage &stage)
		:numTurns(stage.getNumTurns()), currentTurnNo(stage.getCurrentTurnNo()), field(stage.field), agentManager(stage.agentManager), scoreManager(field), commandNormalizer(stage.commandNormalizer)
	{

	}

	Stage::Stage(uint8_t numTurns, const FieldInfo &fieldInfo, const AgentInfo &agentManagerInfo)
		: numTurns(numTurns), currentTurnNo(0), field(fieldInfo), agentManager(agentManagerInfo, field.getSize()), scoreManager(field), commandNormalizer(field, agentManager)
	{
		for(int t = 0; t < numTeams; ++t)
		{
			for(uint8_t i = 0; i < agentManager.getNumAgents(); ++i)
			{
				field.setTileOnPanel(agentManager(static_cast<TeamID>(t), i).getCurrentPosition(), toTile(static_cast<TeamID>(t)));
			}
		}
	}

	void Stage::act(const StageCommand &command)
	{
		const StageCommand &normalizedCommand = commandNormalizer(command);
		updatePanels(normalizedCommand);
		moveAgents(normalizedCommand);
		currentTurnNo++;
	}

	Size Stage::getFieldSize()const noexcept
	{
		return field.getSize();
	}

	uint8_t Stage::getNumAgents()const noexcept
	{
		return agentManager.getNumAgents();
	}

	uint8_t Stage::getNumTurns()const noexcept
	{
		return numTurns;
	}

	uint8_t Stage::getCurrentTurnNo()const noexcept
	{
		return currentTurnNo;
	}

	uint8_t Stage::getNumRemainingTurns()const noexcept
	{
		return numTurns - currentTurnNo;
	}

	Position Stage::getAgentPosition(TeamID team, uint8_t agentNo) const
	{
		return agentManager(team, agentNo).getCurrentPosition();
	}

	bool Stage::canAgentMovePositionally(TeamID team, uint8_t agentNo, Direction direction)const
	{
		return agentManager(team, agentNo).canMovePositionally(direction);
	}

	bool Stage::canAgentAct(TeamID team, uint8_t agentNo, Command command)const
	{
		if(command == CommandID::stay)
		{
			return true;
		}
		ActionID action = command.action;
		if(action == ActionID::doNothing)
		{
			return true;
		}
		Direction direction = command.direction;
		if(!canAgentMovePositionally(team, agentNo, direction))
		{
			return false;
		}
		Position nextPosition = movedPosition(agentManager(team, agentNo).getCurrentPosition(), direction);
		TileID agentTile = toTile(team);
		TileID panelTile = field[nextPosition].getTileStatus();
		return (action == ActionID::removePanel && panelTile != TileID::none) || (action == ActionID::setTileOnPanel && (panelTile == agentTile || panelTile == TileID::none));
	}

	int8_t Stage::getPanelPoint(Position position)const noexcept
	{
		return field[position].getPoint();
	}

	TileID Stage::getPanelTileStatus(Position position)const noexcept
	{
		return field[position].getTileStatus();
	}

	bool Stage::getPanelRegionStatus(Position position, TeamID team)const
	{
		return field[position].getRegionStatus(team);
	}

	bool Stage::isAgentOnPanel(Position position)const noexcept
	{
		for(int t = 0; t < numTeams; ++t)
		{
			for(uint8_t i = 0; i < agentManager.getNumAgents(); ++i)
			{
				if(position == agentManager(static_cast<TeamID>(t), i).getCurrentPosition())
				{
					return true;
				}
			}
		}
		return false;
	}

	Score Stage::getScore()const noexcept
	{
		return scoreManager.getScore();
	}

	StageInterface *Stage::copy()const
	{
		return new Stage(*this);
	}

	void Stage::destroy()
	{
		delete this;
	}
}