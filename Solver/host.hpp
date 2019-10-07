#pragma once

#include "Simulator/stage.hpp"
#include "engine/interface.hpp"


namespace solver
{
	class Host
	{
		simulator::Stage stage;
		engine::Interface *const redEngine;
		engine::Interface *const blueEngine;

	public:
		Host(simulator::FieldInfo fieldInfo, simulator::AgantManagerInfo agentInfo, engine::Interface *redEngine, engine::Interface *blueEngine);
		void startThinking();
		void stopThinking();
		void act();
	};
}