#pragma once

#include "position.hpp"
#include <vector>


namespace solver
{
	class AgentInfo
	{
		uint8_t numAgents;
		std::vector<Position> redAgentInitialPositions;
		std::vector<Position> blueAgentInitialPositions;

	public:
		void setNumAgents(uint8_t numAgents)
		{
			this->numAgents = numAgents;
			redAgentInitialPositions.resize(numAgents);
			blueAgentInitialPositions.resize(numAgents);
		}
		uint8_t getNumAgents()const noexcept
		{
			return numAgents;
		}
		Position &redAgentInitialPosition(uint8_t agentNo)
		{
			return redAgentInitialPositions[agentNo];
		}
		const Position &redAgentInitialPosition(uint8_t agentNo)const
		{
			return redAgentInitialPositions[agentNo];
		}
		Position &blueAgentInitialPosition(uint8_t agentNo)
		{
			return blueAgentInitialPositions[agentNo];
		}
		const Position &blueAgentInitialPosition(uint8_t agentNo)const
		{
			return blueAgentInitialPositions[agentNo];
		}
	};
}