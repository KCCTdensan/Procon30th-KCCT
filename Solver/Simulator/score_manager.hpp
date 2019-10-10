#pragma once

#include "score_updater.hpp"
#include <array>


namespace solver::simulator
{
	class ScoreManager
	{
		std::array<ScoreUpdater, numTeams> scores;

	public:
		ScoreManager(const Field &field)
			: scores{ScoreUpdater(field,TeamID::red), ScoreUpdater(field,TeamID::blue)}
		{

		}
		void update()
		{
			for(TeamID team : TeamID())
			{
				scores[static_cast<size_t>(team)].update();
			}
		}
		Score getScore()const noexcept
		{
			Score ret;
			for(TeamID team : TeamID())
			{
				ret.teamScores[static_cast<size_t>(team)] = scores[static_cast<size_t>(team)].getScore();
			}
			return ret;
		}
	};
}