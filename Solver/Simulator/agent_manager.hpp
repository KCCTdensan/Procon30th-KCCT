#pragma once

#include "agent.hpp"
#include "../agent_info.hpp"
#include <vector>


namespace solver
{
	namespace simulator
	{
		class AgentManager
		{
			uint8_t numAgents;
			const Size fieldSize;
			std::vector<Agent> redAgents;
			std::vector<Agent> blueAgents;

		public:
			AgentManager(const AgantInfo &agentInfo, const Size &fieldSize)
				:numAgents(agentInfo.getNumAgents()), fieldSize(fieldSize)
			{
				for(uint8_t i = 0; i < numAgents; ++i)
				{
					redAgents.emplace_back(fieldSize, agentInfo.getRedAgentInitialPosition(i));
					blueAgents.emplace_back(fieldSize, agentInfo.getBlueAgentInitialPosition(i));
				}
			}
			uint8_t getNumAgents()const noexcept
			{
				return numAgents;
			}
			const Agent &getRedAgent(uint8_t agentNo)const
			{
				return redAgents[agentNo];
			}
			const Agent &getBlueAgent(uint8_t agentNo)const
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