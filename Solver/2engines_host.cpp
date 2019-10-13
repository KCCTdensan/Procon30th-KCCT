#include "2engines_host.hpp"
#include "agent_info.hpp"
#include "1engine_host.hpp"


namespace solver
{
	Host::Host(StageInterface &stage, engine::Interface &redEngine, engine::Interface &blueEngine)
		: stage(stage), redEngine(redEngine), blueEngine(blueEngine)
	{
		redEngine.initialize(TeamID::red, stage);
		blueEngine.initialize(TeamID::blue, stage);
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
		StageCommand command(redEngine.getBestCommands(), blueEngine.getBestCommands());
		stage.act(command);
		redEngine.update(command);
		blueEngine.update(command);
	}
}