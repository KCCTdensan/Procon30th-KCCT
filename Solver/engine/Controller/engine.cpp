#include "engine.hpp"
#include "../../random.hpp"
#include <iostream>


namespace solver::engine::controller
{
	void Engine::initialize(TeamID team, const StageInterface &stage)
	{
		this->team = team;
		numAgents = stage.getNumAgents();
		numRemainingTurns = stage.getNumRemainingTurns();
		this->stage = &stage;
		agentIntentions.commands.resize(numAgents);
	}

	void Engine::startThinking()
	{

	}

	void Engine::stopThinking()
	{
		for(unsigned i = 0; i < numAgents; ++i)
		{
			agentIntentions.commands[i] = static_cast<ActionID>(getRandomValue(0, numActionID));//‰¼ƒvƒƒOƒ‰ƒ€
		}
	}

	const TeamCommand &Engine::getBestActions()const
	{
		return agentIntentions;
	}
}