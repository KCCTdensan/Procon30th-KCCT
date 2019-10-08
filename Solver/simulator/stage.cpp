#include "stage.hpp"


namespace solver::simulator
{
	Stage::Stage(uint8_t numTurns, const FieldInfo &fieldInfo, const AgantInfo &agentManagerInfo)
		:numTurns(numTurns), currentTurnNo(0), field(fieldInfo), agentManager(agentManagerInfo, field.getSize()), scoreManager(field)
	{

	}

	void Stage::act(const Command &commandOfRedTeam, const Command &commandOfBlueTeam)
	{
		//
		scoreManager.update();
	}

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

	bool Stage::canAgentAct(TeamID team_id, uint8_t agentNo, ActionID action_id)const noexcept
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