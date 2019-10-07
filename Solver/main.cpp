#include "engine_loader.hpp"
#include "host.hpp"


solver::FieldInfo createRandomField()
{

}

solver::AgantInfo createRandomAgent()
{

}

int main(int argc, char *argv[])
{
	constexpr unsigned numTurns = 30;

	switch(argc)
	{
	case 1:
		break;

	case 2:
		break;

	default:
		return -1;
	}

	solver::EngineLoader controllerCreator(L"Controller");
	solver::EngineLoader ka31neoCreator(L"KA-31 NEO");

	solver::engine::Interface *controller = controllerCreator.createEngine();
	solver::engine::Interface *ka31neo = ka31neoCreator.createEngine();

	solver::simulator::Stage stage(numTurns, createRandomField(), createRandomAgent());
	solver::Host host(stage, *controller, *ka31neo);

	for(int i = 0; i < numTurns; ++i)
	{
		host.startThinking();
		host.stopThinking();
		host.act();
	}

	controllerCreator.destroyEngine(controller);
	ka31neoCreator.destroyEngine(ka31neo);

	return 0;
}