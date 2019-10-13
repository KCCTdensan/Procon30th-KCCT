#pragma once

#include "server_interface.hpp"
#include "simulator/stage.hpp"
#include "engine/interface.hpp"


namespace solver
{
	class Client
	{
		ServerInterface server;
		simulator::Stage stage;
		engine::Interface &engine;

	public:
		Client(engine::Interface &engine);
		void recieveStage();
		void startThinking();
		void stopThinking();
		void sendCommand();
		const StageInterface &getStage()const noexcept;
	};
}