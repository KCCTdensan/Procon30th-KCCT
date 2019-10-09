#pragma once

#include "agent.hpp"
#include "../agent_info.hpp"
#include "stage_flag.hpp"
#include <array>
#include <vector>


namespace solver::simulator
{
	class AgentManager
	{
		uint8_t numAgents;
		const Size fieldSize;
		std::array<std::vector<Agent>, numTeams> agents;

	public:
		AgentManager(const AgentInfo &agentInfo, const Size &fieldSize)
			:numAgents(agentInfo.getNumAgents()), fieldSize(fieldSize)
		{
			for(TeamID team : TeamID())
			{
				for(uint8_t i = 0; i < numAgents; ++i)
				{
					agents[static_cast<size_t>(team)].emplace_back(fieldSize, team, agentInfo.agentInitialPosition(team, i));
				}
			}
		}
		uint8_t getNumAgents()const noexcept
		{
			return numAgents;
		}
		const Agent &agent(TeamID team, uint8_t agentNo)const
		{
			return agents[static_cast<size_t>(team)][agentNo];
		}
		StageFlag decideNextStayingAgents(const StageFlag &isDecided, const StageCommand &command)
		{
			StageFlag ret(isDecided);
			bool isUpdated;
			do
			{
				isUpdated = false;
				for(TeamID team : TeamID())
				{
					for(uint8_t i = 0; i < numAgents; ++i)
					{
						if(isDecided.agentFlag(team, i))
						{
							continue;
						}
						ActionID agentCommand = command.teamCommands[static_cast<size_t>(team)].commands[i];
						Position nextPosition = movedPosition(this->agent(team, i).getPosition(), agentCommand);
						//移動先のパネルのエージェントが確定していた場合
						if(isDecided.fieldFlag[nextPosition])
						{
							//パネルの上のエージェントを確定させる
							Position agentPosition = this->agent(team, i).getPosition();
							ret.fieldFlag[agentPosition] = true;
							ret.agentFlag(team, i) = true;
							isUpdated = true;
						}
					}
				}
			}
			while(isUpdated);
		}
	};
}