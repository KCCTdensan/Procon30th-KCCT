#pragma once

#include "field_flag.hpp"
#include "agent_flag.hpp"


namespace solver::simulator
{
	struct StageFlag
	{
		FieldFlag fieldFlag;
		AgentFlag agentFlag;

		StageFlag(Size fieldSize, uint8_t numAgents)
			: fieldFlag(fieldSize), agentFlag(numAgents)
		{

		}
	};
}