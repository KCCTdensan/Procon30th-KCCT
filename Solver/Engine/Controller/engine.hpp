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
			//�W�����͂ɂ��G�[�W�F���g�̈ӎv�\����agentIntentions�ϐ��ɕۑ�����
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