#pragma once

#include "../interface.hpp"
#include "agent.hpp"
#include <vector>


namespace solver::engine::ka31neo
{
	class Engine : public Interface
	{
		TeamID team_id;
		unsigned numRemainingTurns;
		std::vector<Agent> agents;
		Command agentIntentions;

	public:
		void initialize(TeamID team_id, const StageInterface &stage);
		void startThinking()override;
		void stopThinking()override;
		const Command &getBestActions()const override;
	};
}