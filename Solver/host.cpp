#include "host.hpp"


namespace solver
{
	Host::Host(engine::Interface *redEngine, engine::Interface *blueEngine)
	{
		this->redEngine = redEngine;
		this->blueEngine = blueEngine;
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
}