#pragma once

#include "field.hpp"
#include "agent_manager.hpp"
#include "../stage_command.hpp"


namespace solver::simulator
{
	class CommandNormalizer
	{
		const Field &field;
		const AgentManager &agentManager;
		
		StageCommand normalizeStage1(const StageCommand &command, StageFlag &flag)const
		{
			StageCommand ret = command;
			const uint8_t numAgents = agentManager.getNumAgents();
			for(int t = 0; t < numTeams; ++t)
			{
				for(uint8_t i = 0; i < numAgents; ++i)
				{
					TeamID team = static_cast<TeamID>(t);
					const Agent &agent = agentManager(team, i);
					CommandID agentCommand = command.teamCommands[t].commands[i];
					Direction commandDirection = Command(agentCommand).direction;
					if(agentCommand == CommandID::stay || !agent.canMovePositionally(commandDirection))
					{
						//�p�l���̏�̃G�[�W�F���g���m�肳����
						Position agentPosition = agent.getCurrentPosition();
						flag.fieldFlag[agentPosition] = true;
						flag.agentFlag(team, i) = true;
						ret.teamCommands[t].commands[i] = CommandID::stay;
					}
				}
			}
			return ret;
		}
		StageCommand normalizeStage2(const StageCommand &command, StageFlag &flag)const
		{
			StageCommand ret = command;
			const uint8_t numAgents = agentManager.getNumAgents();
			FieldFlag<uint8_t> overlappedAgent(field.getSize());
			for(int t = 0; t < numTeams; ++t)
			{
				for(uint8_t i = 0; i < numAgents; ++i)
				{
					TeamID team = static_cast<TeamID>(t);
					if(flag.agentFlag(team, i))
					{
						continue;
					}
					const Agent &agent = agentManager(team, i);
					CommandID agentCommand = command.teamCommands[t].commands[i];
					Position agentPosition = agentManager(team, i).getCurrentPosition();
					Direction commandDirection = Command(agentCommand).direction;
					Position nextPosition = movedPosition(agentPosition, commandDirection);
					//�R�}���h�̎w���ʒu�����Ԃ��Ă����ꍇ
					if(overlappedAgent[nextPosition] != 0)
					{
						//�p�l���̏�̃G�[�W�F���g���m�肳����
						TeamID teamOfAgentOnPanel = static_cast<TeamID>((0x0f & overlappedAgent[nextPosition]) >> 3);
						uint8_t noOfAgentOnPanel = static_cast<uint8_t>(0x07 & overlappedAgent[nextPosition]);
						Position positionOfAgentOnPanel = agentManager(teamOfAgentOnPanel, noOfAgentOnPanel).getCurrentPosition();
						flag.fieldFlag[positionOfAgentOnPanel] = true;
						flag.agentFlag(teamOfAgentOnPanel, noOfAgentOnPanel) = true;
						ret.teamCommands[static_cast<size_t>(teamOfAgentOnPanel)].commands[noOfAgentOnPanel] = CommandID::stay;
						flag.fieldFlag[agentPosition] = true;
						flag.agentFlag(team, i) = true;
						ret.teamCommands[t].commands[i] = CommandID::stay;
						continue;
					}
				}
			}
			return ret;
		}
		StageCommand normalizeStage3(const StageCommand &command, StageFlag &flag)const
		{
			StageCommand ret = command;
			const uint8_t numAgents = agentManager.getNumAgents();
			bool isUpdated;
			do
			{
				isUpdated = false;
				for(int t = 0; t < numTeams; ++t)
				{
					for(uint8_t i = 0; i < numAgents; ++i)
					{
						TeamID team = static_cast<TeamID>(t);
						if(flag.agentFlag(team, i))
						{
							continue;
						}
						const Agent &agent = agentManager(team, i);
						CommandID agentCommand = command.teamCommands[t].commands[i];
						Position agentPosition = agentManager(team, i).getCurrentPosition();
						Direction commandDirection = Command(agentCommand).direction;
						Position nextPosition = movedPosition(agentPosition, commandDirection);
						//�ړ���̃p�l���̃G�[�W�F���g���m�肵�Ă����ꍇ
						if(flag.fieldFlag[nextPosition])
						{
							//�p�l���̏�̃G�[�W�F���g���m�肳����
							flag.fieldFlag[agentPosition] = true;
							flag.agentFlag(team, i) = true;
							ret.teamCommands[t].commands[i] = CommandID::stay;
							isUpdated = true;
							continue;
						}
						//�G�p�l�����͂����ꍇ
						ActionID agentAction = Command(agentCommand).action;
						if(agentAction == ActionID::removePanel)
						{
							//�p�l���̏�̃G�[�W�F���g���m�肳����
							flag.fieldFlag[agentPosition] = true;
							flag.agentFlag(team, i) = true;
							isUpdated = true;
							continue;
						}
					}
				}
			}
			while(isUpdated);
			return ret;
		}

	public:
		CommandNormalizer(const Field &field, const AgentManager &agentManager)
			: field(field), agentManager(agentManager)
		{

		}
		StageCommand operator()(const StageCommand &command)const
		{
			StageFlag stageFlag(field.getSize(), agentManager.getNumAgents());
			const StageCommand &normalizedCommandStage1 = normalizeStage1(command, stageFlag);
			const StageCommand &normalizedCommandStage2 = normalizeStage2(normalizedCommandStage1, stageFlag);
			return normalizeStage3(normalizedCommandStage2, stageFlag);
		}
	};
}