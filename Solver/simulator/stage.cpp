#include "stage.hpp"


namespace solver::simulator
{
	bool Stage::willAgentStay(const Agent &agent, ActionID command)const
	{
		//エージェントが"留まる"を選択したか、意思表示が無効な場合
		return command == ActionID::stay || !agent.canMove(command);
	}

	bool Stage::willAgentRemoveTile(const Agent &agent, ActionID command) const
	{
		Position nextPosition = movedPosition(agent.getPosition(), command);
		TileID tile = field[nextPosition].getTileStatus();
		return tile != TileID::none && agent.getTeam() != toTeam(tile);
	}

	StageFlag Stage::decideFirstAgentStayingPanels(StageCommand &command)const
	{
		StageFlag ret(field.getSize(), agentManager.getNumAgents());
		for(TeamID team : TeamID())
		{
			for(uint8_t i = 0; i < agentManager.getNumAgents(); ++i)
			{
				if(willAgentStay(agentManager.agent(team, i), command.teamCommands[static_cast<size_t>(team)].commands[i]))
				{
					//パネルの上のエージェントを確定させる
					Position agentPosition = agentManager.agent(team, i).getPosition();
					ret.fieldFlag[agentPosition] = true;
					ret.agentFlag(team, i) = true;
					command.teamCommands[static_cast<size_t>(team)].commands[i] = ActionID::stay;
				}
			}
		}
		return ret;
	}

	StageFlag Stage::decideAgentOverlappingPanels(const StageFlag &isDecided, StageCommand &command)const
	{

	}
	
	StageFlag Stage::decideNextStayingAgents(const StageFlag &isDecided, StageCommand &command)const
	{
		StageFlag ret(isDecided);
		bool isUpdated;
		do
		{
			isUpdated = false;
			for(TeamID team : TeamID())
			{
				for(uint8_t i = 0; i < agentManager.getNumAgents(); ++i)
				{
					if(isDecided.agentFlag(team, i))
					{
						continue;
					}
					ActionID agentCommand = command.teamCommands[static_cast<size_t>(team)].commands[i];
					Position nextPosition = movedPosition(agentManager.agent(team, i).getPosition(), agentCommand);
					//移動先のパネルのエージェントが確定していた場合
					if(isDecided.fieldFlag[nextPosition])
					{
						//パネルの上のエージェントを確定させる
						Position agentPosition = agentManager.agent(team, i).getPosition();
						ret.fieldFlag[agentPosition] = true;
						ret.agentFlag(team, i) = true;
						//意思表示が無効なので留まらせる
						command.teamCommands[static_cast<size_t>(team)].commands[i] = ActionID::stay;
						isUpdated = true;
						continue;
					}
					//敵パネルをはがす場合
					if(willAgentRemoveTile(agentManager.agent(team, i), agentCommand))
					{
						//パネルの上のエージェントを確定させる
						Position agentPosition = agentManager.agent(team, i).getPosition();
						ret.fieldFlag[agentPosition] = true;
						ret.agentFlag(team, i) = true;
						isUpdated = true;
						continue;
					}
				}
			}
		}
		while(isUpdated);
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
		StageCommand finalCommand = command;
		StageFlag stayingFlag = decideFirstAgentStayingPanels(finalCommand);
		stayingFlag = decideAgentOverlappingPanels(stayingFlag, finalCommand);
		stayingFlag = decideNextStayingAgents(stayingFlag, finalCommand);

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