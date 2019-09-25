#pragma once

#include "field.hpp"
#include "agent_manager.hpp"
#include "score_manager.hpp"
#include <array>


class Stage
{
	const Field field;
	AgentManager agentManager;
	ScoreManager scoreManager;
	int turnNo;

public:
	Stage(const FieldInfo &fieldInfo, uchar numAgents)
		: field(fieldInfo), agentManager(field, numAgents), scoreManager(field)
	{

	}
	void print()const
	{

	}
};