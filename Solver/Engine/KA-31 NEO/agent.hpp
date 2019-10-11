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

		static unsigned __stdcall startThinking(void *arg);

	public:
		Agent(const Agent &) = delete;
		Agent &operator=(const Agent &) = delete;
		Agent(Agent &&agent)noexcept;
		Agent(TeamID team_id, uint8_t agentNo, const StageInterface &stage);
		~Agent();
		void startThinking();
		void stopThinking();
		ActionID getBestAction()const noexcept;
	};
}