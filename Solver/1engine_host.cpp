#include "1engine_host.hpp"


namespace solver
{
	Client::Client(engine::Interface &engine)
		: stage(server.getStage()), engine(engine)
	{

	}

	void Client::recieveStage()
	{
		const StageCommand &command = server.recieveCommand();
		stage.act(command);
		engine.update(command);
	}

	void Client::startThinking()
	{
		engine.startThinking();
	}

	void Client::stopThinking()
	{
		engine.stopThinking();
	}

	void Client::sendCommand()
	{
		server.sendCommand(engine.getBestCommands());
	}

	const StageInterface &Client::getStage()const noexcept
	{
		return stage;
	}
}
