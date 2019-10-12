#pragma once

#include "../../stage_interface.hpp"
#include <queue>


namespace solver::engine::ka31neo
{
	class Simulator
	{
		const TeamID teamID;
		const int8_t agentNo;
		const StageInterface &currentStage;
		std::queue<ActionID> commandList;
 
		ActionID decideAgentCommand(const StageInterface &stage, TeamID team, uint8_t agentNo)const;
		StageCommand decideCommand(const StageInterface &stage)const;
		float calculateReward(const Score &score)const;

	public:
		Simulator(TeamID teamID, int8_t agentNo, const StageInterface &currentStage);
		float rollout()const;
		bool canAct(ActionID actionID)const noexcept;
		Simulator next(ActionID actionID)const;
	};
}