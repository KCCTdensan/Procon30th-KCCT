#pragma once

#include <array>
#include <vector>


namespace solver::simulator
{
	class AgentFlag
	{
		std::array<std::vector<bool>, numTeams> flags;

	public:
		AgentFlag(uint8_t numAgents)
		{
			for(int t = 0; t < numTeams; ++t)
			{
				flags[t].resize(numAgents);
				for(uint8_t i = 0; i < numAgents; ++i)
				{
					flags[t][i] = false;
				}
			}
		}
		std::vector<bool>::reference operator()(TeamID team, uint8_t agentNo)
		{
			return flags[static_cast<size_t>(team)][agentNo];
		}
		bool operator()(TeamID team, uint8_t agentNo)const
		{
			return flags[static_cast<size_t>(team)][agentNo];
		}
	};
}