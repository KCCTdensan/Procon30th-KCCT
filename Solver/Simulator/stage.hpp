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
			Field field;
			AgentManager agentManager;
			ScoreManager scoreManager;
			unsigned turnNo;

		public:
			Stage(const FieldInfo &fieldInfo, const AgantManagerInfo &agentManagerInfo)
				: field(fieldInfo), agentManager(agentManagerInfo, field.getSize()), scoreManager(field)
			{
				turnNo = 1;
			}
			void act(const Command &commandOfRedTeam, const Command &commandOfBlueTeam)
			{
				//
				scoreManager.updateScore();
			}
		};
	}
}