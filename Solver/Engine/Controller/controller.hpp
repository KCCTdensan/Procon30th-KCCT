#pragma once

#include "../interface.hpp"


namespace solver::engine::controller
{
	class Controller : public Interface
	{
		Command agentIntentions;

	public:
		void setStage(unsigned nunRemainingTurns, const simulator::Stage &stage)override
		{

		}
		void think()override
		{
			//�W�����͂ɂ��G�[�W�F���g�̈ӎv�\����agentIntentions�ϐ��ɕۑ�����
		}
		Command getBestActions()const override
		{
			return agentIntentions;
		}
	};
}