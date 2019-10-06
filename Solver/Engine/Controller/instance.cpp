#include "../instance.hpp"
#include "engine.hpp"


namespace solver::engine
{
	Interface *createEngine()
	{
		return new controller::Engine();
	}
	void destroyEngine(Interface *engine)
	{
		delete engine;
	}
}