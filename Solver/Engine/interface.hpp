#pragma once

#include "../command.hpp"
#include "../Simulator/stage.hpp"


namespace solver::engine
{
	class Interface
	{
	public:
		virtual void initialize(TeamID team, unsigned numAgents) = 0;
		virtual void setStage(unsigned numRemainingTurns, const simulator::Stage &stage) = 0;
		virtual void startThinking() = 0;
		virtual void stopThinking() = 0;
		virtual Command getBestActions()const = 0;
	};
}