#include "host.hpp"


namespace solver
{
	Host::Host(simulator::Stage &stage, engine::Interface &redEngine, engine::Interface &blueEngine)
		: stage(stage), redEngine(redEngine), blueEngine(blueEngine)
	{
		redEngine.initialize(TeamID::red, agentInfo.numAgents);
		blueEngine.initialize(TeamID::blue, agentInfo.numAgents);
	}

	void Host::startThinking()
	{
		redEngine->setStage(numTurns - currentTurnNo, stage);
		blueEngine->setStage(numTurns - currentTurnNo, stage);

		redEngine->startThinking();
		blueEngine->startThinking();
	}

	void Host::stopThinking()
	{
		redEngine->stopThinking();
		blueEngine->stopThinking();
	}

	void Host::act()
	{
		stage.act(redEngine->getBestActions(), blueEngine->getBestActions());
		currentTurnNo++;
	}
}