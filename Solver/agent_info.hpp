#pragma once

#include "position.hpp"
#include <vector>


namespace solver
{
	class AgantInfo
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
		Position &getRedAgentInitialPosition(uint8_t agentNo)
		{
			return redAgentInitialPositions[agentNo];
		}
		const Position &getRedAgentInitialPosition(uint8_t agentNo)const
		{
			return redAgentInitialPositions[agentNo];
		}
		Position &getBlueAgentInitialPosition(uint8_t agentNo)
		{
			return blueAgentInitialPositions[agentNo];
		}
		const Position &getBlueAgentInitialPosition(uint8_t agentNo)const
		{
			return blueAgentInitialPositions[agentNo];
		}
	};
}