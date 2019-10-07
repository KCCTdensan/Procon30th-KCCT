#include "host.hpp"


namespace solver
{
	Host::Host(simulator::FieldInfo fieldInfo, simulator::AgantManagerInfo agentInfo, engine::Interface *redEngine, engine::Interface *blueEngine)
		: stage(fieldInfo, agentInfo), redEngine(redEngine), blueEngine(blueEngine)
	{

	}

	void Host::startThinking()
	{
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
	}
}