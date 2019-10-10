#pragma once

#include "action_id.hpp"
#include "team_id.hpp"
#include <array>
#include <vector>


namespace solver
{
	struct TeamCommand
	{
		std::vector<ActionID> commands;
	};

	struct StageCommand
	{
		std::array<TeamCommand, numTeams> teamCommands;
	};
}