#include "stage.hpp"


namespace solver::simulator
{
	uint8_t Stage::getNumAgents()const noexcept
	{
		return agentManager.getNumAgents();
	}

	uint8_t Stage::getNumTurns()const noexcept
	{
		return numTurns;
	}

	uint8_t Stage::getCurrentTurnNo()const noexcept
	{
		return currentTurnNo;
	}

	uint8_t Stage::getNumRemainingTurns()const noexcept
	{
		return numTurns - currentTurnNo;
	}

	bool Stage::canAgentAct(TeamID team_id, uint8_t agentNo, ActionID action_id) const noexcept
	{
		switch(team_id)
		{
		case TeamID::red:
			return agentManager.getRedAgent(agentNo).canMove(action_id);

		case TeamID::blue:
			return agentManager.getBlueAgent(agentNo).canMove(action_id);

		default:
			return false;
		}
	}
}