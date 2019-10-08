#pragma once

#include "../stage_interface.hpp"
#include "field.hpp"
#include "agent_manager.hpp"
#include "score_manager.hpp"
#include "../command.hpp"


namespace solver::simulator
{
	class Stage : public StageInterface
	{
		const uint8_t numTurns;
		uint8_t currentTurnNo;
		Field field;
		AgentManager agentManager;
		ScoreManager scoreManager;

	public:
		Stage(uint8_t numTurns, const FieldInfo &fieldInfo, const AgantInfo &agentManagerInfo);
		void act(const Command &commandOfRedTeam, const Command &commandOfBlueTeam)override;
		uint8_t getNumAgents()const noexcept override;
		uint8_t getNumTurns()const noexcept override;
		uint8_t getCurrentTurnNo()const noexcept override;
		uint8_t getNumRemainingTurns()const noexcept override;
		bool canAgentAct(TeamID team_id, uint8_t agentNo, ActionID action_id)const noexcept override;
	};
}