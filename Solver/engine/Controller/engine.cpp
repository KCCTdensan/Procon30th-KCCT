#include "engine.hpp"
#include <iostream>


namespace solver::engine::controller
{
	void Engine::setStage(unsigned numRemainingTurns, const simulator::Stage &stage)
	{

	}

	void Engine::startThinking()
	{

	}

	void Engine::stopThinking()
	{
		agentIntentions.actionIDs.clear();
		for(unsigned i = 0; i < numAgents; ++i)
		{
			agentIntentions.actionIDs.push_back(ActionID::stay);//‰¼ƒvƒƒOƒ‰ƒ€
		}
	}
}