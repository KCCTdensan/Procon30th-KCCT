#pragma once

#include "../interface.hpp"


namespace solver::engine::controller
{
	class Engine : public Interface
	{
		TeamID team;
		unsigned numAgents;
		Command agentIntentions;

	public:
		Engine()
		{
			team = TeamID::null;
			numAgents = 0;
		}
		void initialize(TeamID team, unsigned numAgents)override
		{
			this->team = team;
			this->numAgents = numAgents;
		}
		void setStage(unsigned nunRemainingTurns, const simulator::Stage &stage)override;
		void startThinking()override;
		void stopThinking()override;
		Command getBestActions()const override
		{
			return agentIntentions;
		}
	};
}