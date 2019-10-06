#pragma once

#include "../command.hpp"
#include "../Simulator/stage.hpp"
#include <vector>


namespace solver
{
	namespace engine
	{
		class Interface
		{
		public:
			virtual void initialize(TeamID team, unsigned numAgents) = 0;
			virtual void setStage(unsigned numRemainingTurns, const simulator::Stage &stage) = 0;
			virtual void think() = 0;
			virtual void unthink() = 0;
			virtual Command getBestActions()const = 0;
		};
	}
}