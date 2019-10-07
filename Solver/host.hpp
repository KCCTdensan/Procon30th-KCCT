#pragma once

#include "stage_interface.hpp"
#include "engine/interface.hpp"


namespace solver
{
	class Host
	{
		StageInterface &stage;
		engine::Interface &redEngine;
		engine::Interface &blueEngine;

	public:
		Host(StageInterface &stage, engine::Interface &redEngine, engine::Interface &blueEngine);
		void startThinking();
		void stopThinking();
		void act();
		uint8_t getNumAgents()const noexcept;
	};
}