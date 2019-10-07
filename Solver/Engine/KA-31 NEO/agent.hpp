#pragma once

#include "node.hpp"
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
		Agent(TeamID team_id, uint8_t agentNo, const StageInterface &stage);
		void startThinking();
		void stopThinking();
		ActionID getBestAction()const noexcept;
	};
}