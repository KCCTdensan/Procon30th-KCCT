#pragma once

#include "command.hpp"
#include "team_id.hpp"


namespace solver
{
	class StageInterface
	{
	public:
		virtual void act(const Command &commandOfRedTeam, const Command &commandOfBlueTeam) = 0;
		virtual uint8_t getNumAgents()const = 0;
		virtual uint8_t getNumTurns()const = 0;
		virtual uint8_t getCurrentTurnNo()const = 0;
		virtual uint8_t getNumRemainingTurns()const = 0;
		virtual bool canAgentAct(TeamID team_id, uint8_t agentNo)const = 0;
	};
}