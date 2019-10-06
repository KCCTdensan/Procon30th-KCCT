#pragma once

#include "engine/interface.hpp"


namespace solver
{
	class Host
	{
		engine::Interface *redEngine;
		engine::Interface *blueEngine;

	public:
		Host(engine::Interface *redEngine, engine::Interface *blueEngine);
		void startThinking();
		void stopThinking();
	};
}