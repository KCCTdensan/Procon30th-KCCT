#define MODE 0

#if MODE == 0

#include "engine_loader.hpp"
#include "simulator/stage.hpp"
#include "2engines_host.hpp"
#include "cui/stage_printer.hpp"
#include "random.hpp"
#include <iostream>


solver::FieldInfo createRandomField()
{
	solver::FieldInfo ret;
	const solver::Size size(static_cast<uint8_t>(solver::getRandomValue(20, 20)), static_cast<uint8_t>(solver::getRandomValue(10, 20)));
	ret.setSize(size);
	for(uint8_t y = 0; y < size.height; ++y)
	{
		for(uint8_t x = 0; x < size.width; ++x)
		{
			const solver::Position position(static_cast<int8_t>(x), static_cast<int8_t>(y));
			ret[position] = solver::getRandomValue(-16, 16);
		}
	}
	return ret;
}

solver::AgentInfo createRandomAgent(solver::Size fieldSize)
{
	solver::AgentInfo ret;
	const uint8_t numAgents = static_cast<uint8_t>(solver::getRandomValue(8, 8));
	ret.setNumAgents(numAgents);
	for(uint8_t i = 0; i < numAgents; ++i)
	{
		createPosition:
		solver::Position redAgentPosition;
		redAgentPosition.x = solver::getRandomValue(0, fieldSize.width / 2 - 1);
		redAgentPosition.y = solver::getRandomValue(0, fieldSize.height - 1);
		for(uint8_t j = 0; j < i; ++j)
		{
			if(ret.agentInitialPosition(solver::TeamID::red, j) == redAgentPosition)
			{
				goto createPosition;
			}
		}
		ret.agentInitialPosition(solver::TeamID::red, i) = redAgentPosition;
		solver::Position blueAgentPosition;
		blueAgentPosition.x = fieldSize.width - redAgentPosition.x - 1;
		blueAgentPosition.y = redAgentPosition.y;
		ret.agentInitialPosition(solver::TeamID::blue, i) = blueAgentPosition;
	}
	return ret;
}

int main()
{
	constexpr unsigned numTurns = 30;

	solver::EngineLoader ka31neoCreator(L"KA-31 NEO");
	solver::EngineLoader controllerCreator(L"Controller");
	solver::engine::Interface *controller1 = ka31neoCreator.createEngine();
	solver::engine::Interface *controller2 = ka31neoCreator.createEngine();

	solver::FieldInfo fieldInfo = createRandomField();
	solver::AgentInfo agentInfo = createRandomAgent(fieldInfo.getSize());

	solver::simulator::Stage stage(numTurns, fieldInfo, agentInfo);
	solver::Host host(stage, *controller1, *controller2);
	solver::cui::StagePrinter printer(stage);

	printer.print();
	for(int i = 0; i < numTurns; ++i)
	{
		host.startThinking();
		Sleep(5000);
		host.stopThinking();
		host.act();
		printer.print();
	}

	ka31neoCreator.destroyEngine(controller1);
	ka31neoCreator.destroyEngine(controller2);

	return 0;
}


#else

#include "engine_loader.hpp"
#include "1engine_host.hpp"
#include "cui/stage_printer.hpp"


int main()
{
	solver::EngineLoader engineLoader(L"KA-31 NEO");
	solver::engine::Interface *engine = engineLoader.createEngine();
	solver::Client client(*engine);
	solver::cui::StagePrinter printer(client.getStage());
	printer.print();
	//loop
	engineLoader.destroyEngine(engine);
	return 0;
}


#endif