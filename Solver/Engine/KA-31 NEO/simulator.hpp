#pragma once

#include "../../stage_interface.hpp"
#include <queue>


namespace solver::engine::ka31neo
{
	class Simulator
	{
		const TeamID team_id;
		const int8_t agentNo;
		const StageInterface &currentStage;
		std::queue<ActionID> commandList;

	public:
		Simulator(TeamID team_id, int8_t agentNo, const StageInterface &currentStage)
			: team_id(team_id), agentNo(agentNo), currentStage(currentStage)
		{

		}
		float rollout()const
		{
			//StageInterface stage = currentStage;
			for(int i = 0; i < commandList.size(); ++i)
			{

			}
			for(int i = currentStage.getCurrentTurnNo() + commandList.size(); i < currentStage.getNumTurns(); ++i)
			{
				Command redCommand;
				Command blueCommand;
				//stage.act(redCommand, blueCommand);
			}
			//ƒXƒRƒAŽæ“¾
			//•ñV‚ðŒvŽZ
			return 0.0;
		}
		bool canAct(ActionID action_id)const
		{
			return currentStage.canAgentAct(team_id, agentNo);
		}
		Simulator next(ActionID action_id)const
		{
			Simulator ret(team_id, agentNo, currentStage);
			ret.commandList.push(action_id);
			return ret;
		}
	};
}