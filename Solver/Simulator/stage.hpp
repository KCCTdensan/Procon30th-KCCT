#pragma once

#include "field.hpp"
#include "agent_manager.hpp"
#include "score_manager.hpp"
#include "../command.hpp"


namespace solver
{
	namespace simulator
	{
		class Stage
		{
			const uint8_t numTurns;
			uint8_t currentTurnNo;
			Field field;
			AgentManager agentManager;
			ScoreManager scoreManager;

		public:
			Stage(uint8_t numTurns, const FieldInfo &fieldInfo, const AgantManagerInfo &agentManagerInfo)
				:numTurns(numTurns), currentTurnNo(1), field(fieldInfo), agentManager(agentManagerInfo, field.getSize()), scoreManager(field)
			{

			}
			void act(const Command &commandOfRedTeam, const Command &commandOfBlueTeam)
			{
				//
				scoreManager.update();
			}
		};
	}
}