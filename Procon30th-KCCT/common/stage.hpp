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
	Stage(const FieldInfo &fieldInfo, const AgantManagerInfo &agentManagerInfo)
		: field(fieldInfo), agentManager(agentManagerInfo, field), scoreManager(field)
	{
		turnNo = 1;
	}
	void print()const
	{

	}
};