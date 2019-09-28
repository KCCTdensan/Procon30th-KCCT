#pragma once

#include "../interface.hpp"
#include "node.hpp"


namespace solver
{
	namespace engine
	{
		namespace ka31neo
		{
			class KA31Neo : public Interface
			{
				Node *currentNode;

			public:
				KA31Neo()noexcept
				{
					currentNode = nullptr;
				}
				void setStage(unsigned numRemainingTurns, const simulator::Stage &stage)override
				{
					currentNode = new Node(Simulator(numRemainingTurns, stage));
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