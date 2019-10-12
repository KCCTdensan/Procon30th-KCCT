#include "engine.hpp"


namespace solver::engine::ka31neo
{
	void Engine::initialize(TeamID teamID, const StageInterface &stage)
	{
		this->teamID = teamID;
		for(uint8_t i = 0; i < stage.getNumAgents(); ++i)
		{
			agents.emplace_back(Agent(teamID, i, stage));
		}
		agentIntentions.commands.resize(stage.getNumAgents());
	}

	void Engine::startThinking()
	{
		std::fill(agentIntentions.commands.begin(), agentIntentions.commands.end(), CommandID::null);
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
			agentIntentions.commands[i] = agents[i].getBestCommand();
		}
	}

	const TeamCommand &Engine::getBestCommands()const
	{
		return agentIntentions;
	}

	void Engine::update(const StageCommand &command)
	{
		for(Agent &agent : agents)
		{
			agent.updateStage(command);
		}
	}
}