#pragma once

#include "agent.hpp"
#include <vector>


namespace solver
{
	namespace simulator
	{
		struct AgantManagerInfo
		{
			std::vector<Position> redAgentInitialPositions;
			std::vector<Position> blueAgentInitialPositions;
		};

		class AgentManager
		{
			const Size fieldSize;
			std::vector<Agent> redAgents;
			std::vector<Agent> blueAgents;

		public:
			AgentManager(const AgantManagerInfo &agentManagerInfo, const Size &fieldSize)
				: fieldSize(fieldSize)
			{
				for(const Position &position : agentManagerInfo.redAgentInitialPositions)
				{
					redAgents.emplace_back(fieldSize, position);
				}
				for(const Position &position : agentManagerInfo.blueAgentInitialPositions)
				{
					blueAgents.emplace_back(fieldSize, position);
				}
			}
			const Agent &getRedAgent(unsigned agentNo)const
			{
				return redAgents[agentNo];
			}
			const Agent &getBlueAgent(unsigned agentNo)const
			{
				return blueAgents[agentNo];
			}
			bool canMove(std::vector<Direction> redIntentions, std::vector<Direction> blueIntentions)const
			{
				for(size_t i = 0; i < redAgents.size(); ++i)
				{
					if(!redAgents[i].canMove(redIntentions[i]) || !blueAgents[i].canMove(blueIntentions[i]))
					{
						return false;
					}
				}
				//
				return true;
			}
		};
	}
}