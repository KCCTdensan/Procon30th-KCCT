#pragma once

#include "../../Simulator/stage.hpp"
#include <queue>


namespace solver
{
	namespace engine
	{
		namespace ka31neo
		{
			class Simulator
			{
				const unsigned numRemainingTurns;
				const simulator::Stage currentStage;
				std::queue<ActionID> actionList;


			public:
				Simulator(unsigned numRemainingTurns, const simulator::Stage &currentStage)
					: numRemainingTurns(numRemainingTurns), currentStage(currentStage)
				{

				}
				float rollout()const
				{

				}
				bool canAct(ActionID action_id)const
				{

				}
				Simulator next(ActionID action_id)const
				{
					Simulator ret(numRemainingTurns - 1, currentStage);
					ret.actionList.push(action_id);
					return ret;
				}
			};
		}
	}
}