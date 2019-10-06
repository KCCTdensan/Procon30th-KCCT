#pragma once

#include "../interface.hpp"


namespace solver::engine::controller
{
	class Engine : public Interface
	{
		Command agentIntentions;

	public:
		void initialize(TeamID team, unsigned numAgents)override
		{

		}
		void setStage(unsigned nunRemainingTurns, const simulator::Stage &stage)override
		{

		}
		void think()override
		{
			//標準入力によりエージェントの意思表示をagentIntentions変数に保存する
		}
		void unthink()override
		{

		}
		Command getBestActions()const override
		{
			return agentIntentions;
		}
	};
}