#include "host.hpp"
#include "agent_info.hpp"


namespace solver
{
	Host::Host(simulator::Stage &stage, engine::Interface &redEngine, engine::Interface &blueEngine)
		: stage(stage), redEngine(redEngine), blueEngine(blueEngine)
	{
		redEngine.initialize(TeamID::red, stage.getNumAgents());
		blueEngine.initialize(TeamID::blue, stage.getNumAgents());
	}

	void Host::startThinking()
	{
		redEngine.startThinking();
		blueEngine.startThinking();
	}

	void Host::stopThinking()
	{
		redEngine.stopThinking();
		blueEngine.stopThinking();
	}

	void Host::act()
	{
		stage.act(redEngine.getBestActions(), blueEngine.getBestActions());
	}

	uint8_t Host::getNumAgents()const noexcept
	{
		return stage.getNumAgents();
	}
}