#include "agent.hpp"
#include <process.h>


namespace solver::engine::ka31neo
{
	Agent::Agent(TeamID team, uint8_t agentNo, const simulator::Stage &stage)
	{
		currentNode = new Node(Simulator(team, agentNo, stage));
	}

	void Agent::startThinking()
	{
		isThinking = true;
		threadHandle = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, startThinking, this, 0, &threadID));
		if(threadHandle == NULL)
		{
			throw L"solver::engine::ka31neo::Agent : ƒXƒŒƒbƒh‚Ìì¬‚É¸”s‚µ‚Ü‚µ‚½";
		}
	}

	void Agent::stopThinking()
	{
		isThinking = false;
		WaitForSingleObject(threadHandle, INFINITE);
		CloseHandle(threadHandle);
	}

	ActionID Agent::getBestAction()const noexcept
	{

	}
}