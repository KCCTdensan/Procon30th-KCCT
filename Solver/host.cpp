#include "host.hpp"
#include "agent_info.hpp"


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
		StageCommand command;
		command.teamCommands[static_cast<size_t>(TeamID::red)] = redEngine.getBestActions();
		command.teamCommands[static_cast<size_t>(TeamID::blue)] = blueEngine.getBestActions();
		stage.act(command);
	}

	uint8_t Host::getNumAgents()const noexcept
	{
		return stage.getNumAgents();
	}
}