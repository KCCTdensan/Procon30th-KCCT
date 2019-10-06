#pragma once

#include "../interface.hpp"
#include "agent.hpp"
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
				std::vector<Agent> agents;

			public:
				void initialize(TeamID team, unsigned numAgents)override
				{
					this->team = team;
					agents.resize(numAgents);
				}
				void setStage(unsigned numRemainingTurns, const simulator::Stage &stage)override
				{

				}
				void think()override
				{
					for(Agent &agent : agents)
					{
						agent.think();
					}
				}
				void unthink()override
				{
					for(Agent &agent : agents)
					{
						agent.unthink();
					}
				}
				Command getBestActions()const override
				{

				}
			};
		}
	}
}