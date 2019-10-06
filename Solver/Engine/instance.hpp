#pragma once

#include "interface.hpp"

#ifdef ENGINE
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API __declspec(dllimport)
#endif


namespace solver::engine
{
	extern "C" PLUGIN_API Interface *createEngine();
	extern "C" PLUGIN_API void destroyEngine(Interface *engine);
}