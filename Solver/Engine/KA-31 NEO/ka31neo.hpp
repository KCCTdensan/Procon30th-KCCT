#pragma once

#include "../interface.hpp"


namespace solver
{
	namespace engine
	{
		namespace ka31neo
		{
			class KA31Neo : public Interface
			{
			public:
				void setStage(const simulator::Stage &stage)override
				{

				}
				void think()override
				{

				}
				Command getBestActions()const override
				{

				}
			};
		}
	}
}