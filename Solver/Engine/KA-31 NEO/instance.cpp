#include "../instance.hpp"
#include "engine.hpp"


namespace solver::engine
{
	Interface *createEngine()
	{
		return new ka31neo::Engine;
	}

	void destroyEngine(Interface *engine)
	{
		delete engine;
	}
}