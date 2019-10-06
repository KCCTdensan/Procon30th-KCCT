#pragma once

#include "../interface.hpp"
#include "node.hpp"
#include <vector>


namespace solver
{
	namespace engine
	{
		namespace ka31neo
		{
			class KA31Neo : public Interface
			{
				TeamID team;
				std::vector<Node *> currentNodes;

			public:
				void initialize(TeamID team, unsigned numAgents)override
				{
					this->team = team;
					currentNodes.resize(numAgents);
				}
				void setStage(unsigned numRemainingTurns, const simulator::Stage &stage)override
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