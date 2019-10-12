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
		const uint8_t numAgents;
		const Size fieldSize;
		std::array<std::vector<Agent>, numTeams> agents;

	public:
		AgentManager(const AgentInfo &agentInfo, Size fieldSize)
			:numAgents(agentInfo.getNumAgents()), fieldSize(fieldSize)
		{
			for(int t = 0; t < numTeams; ++t)
			{
				for(uint8_t i = 0; i < numAgents; ++i)
				{
					agents[t].emplace_back(Agent(this->fieldSize, static_cast<TeamID>(t), i, agentInfo.agentInitialPosition(static_cast<TeamID>(t), i)));
				}
			}
		}
		uint8_t getNumAgents()const noexcept
		{
			return numAgents;
		}
		const Agent &operator()(TeamID team, uint8_t agentNo)const
		{
			return agents[static_cast<size_t>(team)][agentNo];
		}
		void move(const std::array<std::vector<Direction>, numTeams> &directions)
		{
			for(int t = 0; t < numTeams; ++t)
			{
				for(uint8_t i = 0; i < numAgents; ++i)
				{
					agents[t][i].move(directions[t][i]);
				}
			}
		}
	};
}