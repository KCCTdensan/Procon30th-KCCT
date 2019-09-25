#pragma once

#include "agent.hpp"


class AgentManager
{
	const Size fieldSize;
	std::vector<Agent> redAgents;
	std::vector<Agent> blueAgents;

public:
	AgentManager(const Field &field, uchar numAgents)
		: fieldSize(field.getSize())
	{
		redAgents.resize(numAgents);
		blueAgents.resize(numAgents);
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