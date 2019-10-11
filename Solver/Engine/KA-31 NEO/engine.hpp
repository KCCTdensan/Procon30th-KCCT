#pragma once

#include "../interface.hpp"
#include "agent.hpp"
#include <vector>


namespace solver::engine::ka31neo
{
	class Engine : public Interface
	{
		TeamID teamID;
		unsigned numRemainingTurns;
		std::vector<Agent> agents;
		TeamCommand agentIntentions;

	public:
		void initialize(TeamID teamID, const StageInterface &stage);
		void startThinking()override;
		void stopThinking()override;
		const TeamCommand &getBestActions()const override;
		void update(const StageCommand &command);
	};
}