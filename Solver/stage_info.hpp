#pragma once

#include "field_info.hpp"
#include "agent_info.hpp"


namespace solver
{
	struct StageInfo
	{
		FieldInfo fieldInfo;
		AgentInfo agentInfo;
	};
}