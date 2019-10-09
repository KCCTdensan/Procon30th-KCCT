#pragma once

#include "position.hpp"
#include <array>
#include <vector>


namespace solver
{
	class AgentInfo
	{
		uint8_t numAgents;
		std::array<std::vector<Position>, numTeams> agentInitialPositions;

	public:
		void setNumAgents(uint8_t numAgents)
		{
			this->numAgents = numAgents;
			for(int t = 0; t < numTeams; ++t)
			{
				agentInitialPositions[t].resize(numAgents);
			}
		}
		uint8_t getNumAgents()const noexcept
		{
			return numAgents;
		}
		Position &agentInitialPosition(TeamID team, uint8_t agentNo)
		{
			return agentInitialPositions[static_cast<size_t>(team)][agentNo];
		}
		Position agentInitialPosition(TeamID team, uint8_t agentNo)const
		{
			return agentInitialPositions[static_cast<size_t>(team)][agentNo];
		}
	};
}