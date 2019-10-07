#pragma once

#include "Simulator/stage.hpp"
#include "engine/interface.hpp"


namespace solver
{
	class Host
	{
		simulator::Stage &stage;
		engine::Interface &redEngine;
		engine::Interface &blueEngine;

	public:
		Host(simulator::Stage &stage, engine::Interface &redEngine, engine::Interface &blueEngine);
		void startThinking();
		void stopThinking();
		void act();
		uint8_t getNumAgents()const noexcept;
	};
}