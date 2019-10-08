#include "engine_loader.hpp"
#include "simulator/stage.hpp"
#include "host.hpp"
#include "cui/stage_printer.hpp"
#include "random.hpp"


solver::FieldInfo createRandomField()
{
	solver::FieldInfo ret;
	const solver::Size size = {solver::getRandomValue(10, 20), solver::getRandomValue(10, 20)};
	ret.setSize(size);
	for(uint8_t y = 0; y < size.height; ++y)
	{
		for(uint8_t x = 0; x < size.width; ++x)
		{
			const solver::Position position = {x,y};
			ret[position] = solver::getRandomValue(-16, 16);
		}
	}
	return ret;
}

solver::AgantInfo createRandomAgent(solver::Size fieldSize)
{
	solver::AgantInfo ret;
	const uint8_t numAgents = static_cast<uint8_t>(solver::getRandomValue(2, 8));
	ret.setNumAgents(numAgents);
	for(uint8_t i = 0; i < numAgents; ++i)
	{

	}
	return ret;
}

int main(int argc, char *argv[])
{
	return 0;

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
	solver::cui::StagePrinter printer(stage);

	printer.print();
	for(int i = 0; i < numTurns; ++i)
	{
		host.startThinking();
		host.stopThinking();
		host.act();
		printer.print();
	}

	controllerCreator.destroyEngine(controller);
	ka31neoCreator.destroyEngine(ka31neo);

	return 0;
}