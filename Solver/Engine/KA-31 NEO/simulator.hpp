#pragma once

#include "../../Simulator/stage.hpp"
#include <queue>


namespace solver::engine::ka31neo
{
	class Simulator
	{
		const TeamID team;
		const int8_t agentNo;
		const unsigned numRemainingTurns;
		const simulator::Stage &currentStage;
		std::queue<ActionID> commandList;

	public:
		Simulator(TeamID team, int8_t agentNo, unsigned numRemainingTurns, const simulator::Stage &currentStage)
			: team(team), agentNo(agentNo), numRemainingTurns(numRemainingTurns), currentStage(currentStage)
		{

		}
		float rollout()const
		{
			simulator::Stage stage = currentStage;
			for(int i = 0; i < commandList.size(); ++i)
			{

			}
			for(int i = 0; i < numRemainingTurns; ++i)
			{
				Command redCommand;
				Command blueCommand;
				stage.act(redCommand, blueCommand);
			}
			//ƒXƒRƒAŽæ“¾
			//•ñV‚ðŒvŽZ
			return 0.0;
		}
		bool canAct(ActionID action_id)const
		{

		}
		Simulator next(ActionID action_id)const
		{
			Simulator ret(team, agentNo, numRemainingTurns - 1, currentStage);
			ret.commandList.push(action_id);
			return ret;
		}
	};
}