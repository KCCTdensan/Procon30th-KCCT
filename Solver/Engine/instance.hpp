#pragma once

#include "interface.hpp"


namespace solver::engine
{
	extern "C" Interface *createEngine();
	extern "C" void destroyEngine(Interface *engine);
}