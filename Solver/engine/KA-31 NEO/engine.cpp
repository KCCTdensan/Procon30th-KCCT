#include "engine.hpp"


namespace solver::engine::ka31neo
{
	void Engine::initialize(TeamID team_id, const StageInterface &stage)
	{
		this->team_id = team_id;
		for(uint8_t i = 0; i < stage.getNumAgents(); ++i)
		{
			agents.emplace_back(team_id, i, stage);
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
		for(uint8_t i = 0; i < agents.size(); ++i)
		{
			agentIntentions.commands[i] = agents[i].getBestAction();
		}
	}

	const TeamCommand &Engine::getBestActions()const
	{
		return agentIntentions;
	}
}