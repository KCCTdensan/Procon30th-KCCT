#pragma once

#include "../interface.hpp"


namespace solver
{
	namespace engine
	{
		namespace controller
		{
			class Controller : public Interface
			{
				Command agentIntentions;

			public:
				void setStage(const simulator::Stage &stage)override
				{

				}
				void think()override
				{
					//標準入力によりエージェントの意思表示をagentIntentions変数に保存する
				}
				Command getBestActions()const override
				{
					return agentIntentions;
				}
			};
		}
	}
}