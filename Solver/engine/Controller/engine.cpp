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
		agentCommands.commands.resize(numAgents);
	}

	void Engine::startThinking()
	{

	}

	void Engine::stopThinking()
	{
		for(unsigned i = 0; i < numAgents; ++i)
		{
			agentCommands.commands[i] = static_cast<CommandID>(getRandomValue(0, numCommandID));//‰¼ƒvƒƒOƒ‰ƒ€
		}
	}

	const TeamCommand &Engine::getBestCommands()const
	{
		return agentCommands;
	}

	void Engine::update(const StageCommand &command)
	{

	}
}