#pragma once

#include "../../Simulator/stage.hpp"


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



			public:
				Simulator(unsigned numRemainingTurns, const simulator::Stage &currentStage)
					: numRemainingTurns(numRemainingTurns), currentStage(currentStage)
				{

				}
				float rollout()
				{

				}
				bool canAct(ActionID action_id)
				{

				}
				Simulator next(ActionID action_id)
				{

				}
			};
		}
	}
}