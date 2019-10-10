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
		void move(StageCommand normalizedCommand)
		{
			for(TeamID team : TeamID())
			{
				for(uint8_t i = 0; i < numAgents; ++i)
				{
					agents[static_cast<size_t>(team)][i].move(normalizedCommand.teamCommands[static_cast<size_t>(team)].commands[i]);
				}
			}
		}
	};
}