#include "engine.hpp"


namespace solver::engine::ka31neo
{
	void Engine::initialize(TeamID team, const simulator::Stage &stage)
	{
		this->team = team;
		for(uint8_t i = 0; i < stage.getNumAgents(); ++i)
		{
			agents.emplace_back(team, i, stage);
		}
	}

	void Engine::startThinking()
	{
		for(Agent &agent : agents)
		{
			agent.startThinking();
		}
	}

	void Engine::stopThinking()
	{
		for(Agent &agent : agents)
		{
			agent.stopThinking();
		}
	}

	Command Engine::getBestActions()const
	{
		return agentIntentions;
	}
}