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
				bool canAct(ActionID action_id)
				{

				}
				Simulator act(ActionID action_id)
				{

				}
			};
		}
	}
}