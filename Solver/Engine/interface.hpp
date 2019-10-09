#pragma once

#include "../team_id.hpp"
#include "../stage_interface.hpp"


namespace solver::engine
{
	class Interface
	{
	public:
		virtual void initialize(TeamID team_id, const StageInterface &stage) = 0;
		virtual void startThinking() = 0;
		virtual void stopThinking() = 0;
		virtual const Command &getBestActions()const = 0;
	};
}