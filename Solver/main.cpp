#include "engine_loader.hpp"
#include "simulator/stage.hpp"
#include "host.hpp"
#include "cui/stage_printer.hpp"
#include "random.hpp"
#include <iostream>


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

solver::AgentInfo createRandomAgent(solver::Size fieldSize)
{
	solver::AgentInfo ret;
	const uint8_t numAgents = static_cast<uint8_t>(solver::getRandomValue(2, 8));
	ret.setNumAgents(numAgents);
	for(uint8_t i = 0; i < numAgents; ++i)
	{
		createPosition:
		solver::Position redAgentPosition;
		redAgentPosition.x = solver::getRandomValue(0, fieldSize.width / 2 - 1);
		redAgentPosition.y = solver::getRandomValue(0, fieldSize.height - 1);
		for(uint8_t j = 0; j < i; ++j)
		{
			if(ret.redAgentInitialPosition(j) == redAgentPosition)
			{
				goto createPosition;
			}
		}
		ret.redAgentInitialPosition(i) = redAgentPosition;
		solver::Position blueAgentPosition;
		blueAgentPosition.x = fieldSize.width - redAgentPosition.x - 1;
		blueAgentPosition.y = redAgentPosition.y;
		ret.blueAgentInitialPosition(i) = blueAgentPosition;
	}
	return ret;
}

int main(int argc, char *argv[])
{
	//return 0;

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
	solver::engine::Interface *controller1 = controllerCreator.createEngine();
	solver::engine::Interface *controller2 = controllerCreator.createEngine();

	solver::FieldInfo fieldInfo = createRandomField();
	solver::AgentInfo agentInfo = createRandomAgent(fieldInfo.getSize());

	solver::simulator::Stage stage(numTurns, fieldInfo, agentInfo);
	solver::Host host(stage, *controller1, *controller2);
	solver::cui::StagePrinter printer(stage);

	printer.print();
	for(int i = 0; i < numTurns; ++i)
	{
		host.startThinking();
		host.stopThinking();
		host.act();
		printer.print();
		Sleep(3000);
	}

	controllerCreator.destroyEngine(controller1);
	controllerCreator.destroyEngine(controller2);

	return 0;
}