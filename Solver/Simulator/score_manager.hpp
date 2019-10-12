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
			for(int t = 0; t < numTeams; ++t)
			{
				scores[t].update();
			}
		}
		Score getScore()const noexcept
		{
			Score ret;
			for(int t = 0; t < numTeams; ++t)
			{
				ret.teamScores[t] = scores[t].getScore();
			}
			return ret;
		}
	};
}