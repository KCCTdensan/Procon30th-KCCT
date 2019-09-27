#pragma once

#include "action_id.hpp"
#include <vector>


namespace solver
{
	struct Command
	{
		std::vector<ActionID> actionIDs;
	};
}