#include "stage.hpp"


namespace solver::simulator
{
	bool Stage::willAgentStay(const Agent &agent, ActionID command)const
	{
		//�G�[�W�F���g��"���܂�"��I���������A�ӎv�\���������ȏꍇ
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
					//�p�l���̏�̃G�[�W�F���g���m�肳����
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
					//�ړ���̃p�l���̃G�[�W�F���g���m�肵�Ă����ꍇ
					if(isDecided.fieldFlag[nextPosition])
					{
						//�p�l���̏�̃G�[�W�F���g���m�肳����
						Position agentPosition = agentManager.agent(team, i).getPosition();
						ret.fieldFlag[agentPosition] = true;
						ret.agentFlag(team, i) = true;
						//�ӎv�\���������Ȃ̂ŗ��܂点��
						command.teamCommands[static_cast<size_t>(team)].commands[i] = ActionID::stay;
						isUpdated = true;
						continue;
					}
					//�G�p�l�����͂����ꍇ
					if(willAgentRemoveTile(agentManager.agent(team, i), agentCommand))
					{
						//�p�l���̏�̃G�[�W�F���g���m�肳����
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