#pragma once

#include "command.hpp"
#include "team_id.hpp"
#include <array>
#include <vector>


namespace solver
{
	struct TeamCommand
	{
		std::vector<CommandID> commands;

		TeamCommand()
		{

		}
		TeamCommand(uint8_t numAgents)
		{
			commands.resize(numAgents);
		}
	};

	struct StageCommand
	{
		std::array<TeamCommand, numTeams> teamCommands;

		StageCommand(uint8_t numAgents)
			: teamCommands {numAgents, numAgents}
		{

		}
		StageCommand(const TeamCommand &redTeamCommand, const TeamCommand &blueTeamCommand)
			: teamCommands {redTeamCommand,blueTeamCommand}
		{

		}
	};
}