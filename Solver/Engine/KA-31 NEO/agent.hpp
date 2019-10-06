#pragma once

#include "node.hpp"
#include <process.h>
#include <Windows.h>


namespace solver::engine::ka31neo
{
	class Agent
	{
		Node *currentNode;
		bool isThinking;
		HANDLE threadHandle;
		DWORD32 threadID;

		static unsigned __stdcall startThinking(void *arg)
		{
			Agent &agent = *reinterpret_cast<Agent *>(arg);
			while(agent.isThinking)
			{
				agent.currentNode->search();
			}
			return 0;
		}

	public:
		Agent(TeamID team)
		{

		}
		void setStage(unsigned numRemainingTurns, const simulator::Stage &stage)
		{

		}
		bool think()
		{
			isThinking = true;
			threadHandle = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, startThinking, this, 0, &threadID));
			return threadHandle != NULL;
		}
		void unthink()
		{
			isThinking = false;
			WaitForSingleObject(threadHandle, INFINITE);
			CloseHandle(threadHandle);
		}
	};
}