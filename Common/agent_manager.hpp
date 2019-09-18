#pragma once

#include "agent.hpp"


class AgentManager
{
	std::vector<Agent> redAgents;
	std::vector<Agent> blueAgents;

public:
	AgentManager(const Field &field, uchar numAgents)
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
	bool canMove(std::vector<Direction> redIntentions, std::vector<Direction> blueIntentions)
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