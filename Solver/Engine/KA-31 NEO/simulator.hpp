#pragma once

#include "../../stage_interface.hpp"
#include <queue>


namespace solver::engine::ka31neo
{
	class Simulator
	{
		const TeamID team_id;
		const int8_t agentNo;
		const StageInterface &currentStage;
		std::queue<ActionID> commandList;

		StageCommand getRandomCommand(uint8_t numAgents)const;
		float calculateReward(const Score &score)const;

	public:
		Simulator(TeamID team_id, int8_t agentNo, const StageInterface &currentStage);
		float rollout()const;
		bool canAct(ActionID action_id)const noexcept;
		Simulator next(ActionID action_id)const;
	};
}