#pragma once

#include "../interface.hpp"


namespace solver::engine::controller
{
	class Engine : public Interface
	{
		TeamID team;
		unsigned numAgents;
		unsigned numRemainingTurns;
		TeamCommand agentCommands;

	public:
		Engine()
		{
			team = TeamID::null;
			numAgents = 0;
			numRemainingTurns = 0;
		}
		void initialize(TeamID team, const StageInterface &stage);
		void startThinking()override;
		void stopThinking()override;
		const TeamCommand &getBestCommands()const override;
		void update(const StageCommand &command);
	};
}