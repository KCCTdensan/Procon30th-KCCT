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
					const TeamID team = static_cast<TeamID>(t);
					const Agent &agent = agentManager(team, i);
					const CommandID agentCommand = command.teamCommands[t].commands[i];
					if(agentCommand == CommandID::stay || !canAgentAct(team, i, agentCommand))
					{
						//パネルの上のエージェントを確定させる
						const Position agentPosition = agent.getCurrentPosition();
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
					const TeamID team = static_cast<TeamID>(t);
					if(flag.agentFlag(team, i))
					{
						continue;
					}
					const Agent &agent = agentManager(team, i);
					const CommandID agentCommand = command.teamCommands[t].commands[i];
					const Position agentPosition = agent.getCurrentPosition();
					const Direction commandDirection = Command(agentCommand).direction;
					const Position nextPosition = movedPosition(agentPosition, commandDirection);
					//コマンドの指定先位置がかぶっていた場合
					if(overlappedAgent[nextPosition] != 0)
					{
						//パネルの上のエージェントを確定させる
						const TeamID teamOfAgentOnPanel = static_cast<TeamID>((0x0f & overlappedAgent[nextPosition]) >> 3);
						const uint8_t noOfAgentOnPanel = static_cast<uint8_t>(0x07 & overlappedAgent[nextPosition]);
						const Position positionOfAgentOnPanel = agentManager(teamOfAgentOnPanel, noOfAgentOnPanel).getCurrentPosition();
						flag.fieldFlag[positionOfAgentOnPanel] = true;
						flag.agentFlag(teamOfAgentOnPanel, noOfAgentOnPanel) = true;
						ret.teamCommands[static_cast<size_t>(teamOfAgentOnPanel)].commands[noOfAgentOnPanel] = CommandID::stay;
						flag.fieldFlag[agentPosition] = true;
						flag.agentFlag(team, i) = true;
						ret.teamCommands[t].commands[i] = CommandID::stay;
						continue;
					}
					overlappedAgent[nextPosition] = 0xf0 | (t << 3) | i;
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
						const TeamID team = static_cast<TeamID>(t);
						if(flag.agentFlag(team, i))
						{
							continue;
						}
						const Agent &agent = agentManager(team, i);
						const CommandID agentCommand = command.teamCommands[t].commands[i];
						const Position agentPosition = agentManager(team, i).getCurrentPosition();
						const Direction commandDirection = Command(agentCommand).direction;
						const Position nextPosition = movedPosition(agentPosition, commandDirection);
						//移動先のパネルのエージェントが確定していた場合
						if(flag.fieldFlag[nextPosition])
						{
							//パネルの上のエージェントを確定させる
							flag.fieldFlag[agentPosition] = true;
							flag.agentFlag(team, i) = true;
							ret.teamCommands[t].commands[i] = CommandID::stay;
							isUpdated = true;
							continue;
						}
						//敵パネルをはがす場合
						ActionID agentAction = Command(agentCommand).action;
						if(agentAction == ActionID::removePanel)
						{
							//パネルの上のエージェントを確定させる
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
		bool canAgentAct(TeamID team, uint8_t agentNo, Command command)const
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
			if(!agentManager(team, agentNo).canMovePositionally(direction))
			{
				return false;
			}
			Position nextPosition = movedPosition(agentManager(team, agentNo).getCurrentPosition(), direction);
			TileID agentTile = toTile(team);
			TileID panelTile = field[nextPosition].getTileStatus();
			return (action == ActionID::removePanel && panelTile != TileID::none) || (action == ActionID::setTileOnPanel && (panelTile == agentTile || panelTile == TileID::none));
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