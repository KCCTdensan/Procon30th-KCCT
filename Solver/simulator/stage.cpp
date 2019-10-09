#include "stage.hpp"


namespace solver::simulator
{
	bool Stage::willAgentStay(const Agent &agent, ActionID command) const
	{
		//エージェントが"留まる"を選択したか、意思表示が無効な場合
		if(command == ActionID::stay || !agent.canMove(command))
		{
			return true;
		}
		Position nextPosition = movedPosition(agent.getPosition(), command);
		TileID tile = field[nextPosition].getTileStatus();
		return tile != TileID::none && agent.getTeam() != toTeam(tile);
	}

	FieldFlag Stage::decideAgentFirstStayingPanels(const StageCommand &command)const
	{
		FieldFlag ret(field.getSize());
		for(TeamID team : TeamID())
		{
			for(uint8_t i = 0; i < agentManager.getNumAgents(); ++i)
			{
				if(willAgentStay(agentManager.agent(team, i), command.teamCommands[static_cast<size_t>(team)].commands[i]))
				{
					//パネルの上のエージェントを確定させる
					Position agentPosition = agentManager.agent(team, i).getPosition();
					ret[agentPosition] = true;
				}
			}
		}
		return ret;
	}

	Stage::Stage(uint8_t numTurns, const FieldInfo &fieldInfo, const AgentInfo &agentManagerInfo)
		:numTurns(numTurns), currentTurnNo(0), field(fieldInfo), agentManager(agentManagerInfo, field.getSize()), scoreManager(field)
	{
		for(TeamID team : TeamID())
		{
			for(uint8_t i = 0; i < agentManager.getNumAgents(); ++i)
			{

			}
		}
	}

	void Stage::act(const StageCommand &command)
	{
		//
		scoreManager.update();
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

	bool Stage::canAgentAct(TeamID team_id, uint8_t agentNo, ActionID action_id)const noexcept
	{
		return agentManager.agent(team_id, agentNo).canMove(action_id);
	}

	int8_t Stage::getPanelPoint(Position position)const noexcept
	{
		return field[position].getPoint();
	}

	TileID Stage::getPanelTileStatus(Position position)const noexcept
	{
		return field[position].getTileStatus();
	}

	bool Stage::getPanelRegionStatus(Position position, TeamID team)const noexcept
	{
		return field[position].getRegionStatus(team);
	}

	bool Stage::isAgentOnPanel(Position position)const noexcept
	{
		for(TeamID team : TeamID())
		{
			for(uint8_t i = 0; i < agentManager.getNumAgents(); ++i)
			{
				if(position == agentManager.agent(team, i).getPosition())
				{
					return true;
				}
			}
		}
		return false;
	}
}