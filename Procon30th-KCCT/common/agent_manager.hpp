#pragma once

#include "agent.hpp"


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
	AgentManager(const AgantManagerInfo &agentManagerInfo, const Field &field)
		: fieldSize(field.getSize())
	{
		for(const Position &position : agentManagerInfo.redAgentInitialPositions)
		{
			redAgents.emplace_back(field, position);
		}
		for(const Position &position : agentManagerInfo.blueAgentInitialPositions)
		{
			blueAgents.emplace_back(field, position);
		}
	}
	const Agent &getRedAgent(uchar agentNo)const
	{
		return redAgents[agentNo];
	}
	const Agent &getBlueAgent(uchar agentNo)const
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
		std::vector<std::vector<uchar>> panels;
		panels.resize(fieldSize.height);
		return true;
	}
};