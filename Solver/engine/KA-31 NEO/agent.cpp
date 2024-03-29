#include "agent.hpp"
#include <process.h>


namespace solver::engine::ka31neo
{
	unsigned __stdcall Agent::startThinking(void *arg)
	{
		Agent &agent = *reinterpret_cast<Agent *>(arg);
		while(agent.isThinking)
		{
			agent.currentNode->search();
		}
		return 0;
	}

	Agent::Agent(Agent &&agent)noexcept
		: team(agent.team), agentNo(agent.agentNo)
	{
		this->currentNode = agent.currentNode;
		this->isThinking = agent.isThinking;
		this->threadHandle = agent.threadHandle;
		this->threadID = agent.threadID;
		agent.currentNode = nullptr;
		agent.isThinking = false;
	}

	Agent::Agent(TeamID teamID, uint8_t agentNo, const StageInterface &stage)
		: team(teamID), agentNo(agentNo), isThinking(false), threadHandle(NULL), threadID(0)
	{
		currentNode = new Node(Simulator(teamID, agentNo, stage));
	}

	Agent::~Agent()
	{
		if(isThinking)
		{
			stopThinking();
		}
		delete currentNode;
	}

	void Agent::startThinking()
	{
		isThinking = true;
		threadHandle = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, startThinking, this, 0, &threadID));
		if(threadHandle == NULL)
		{
			throw L"solver::engine::ka31neo::Agent : スレッドの作成に失敗しました";
		}
	}

	void Agent::stopThinking()
	{
		isThinking = false;
		WaitForSingleObject(threadHandle, INFINITE);
		CloseHandle(threadHandle);
	}

	CommandID Agent::getBestCommand()const noexcept
	{
		return currentNode->getBestCommand();
	}

	void Agent::updateStage(const StageCommand &command)
	{
		currentNode = currentNode->prune(command.teamCommands[static_cast<size_t>(team)].commands[agentNo]);
	}
}