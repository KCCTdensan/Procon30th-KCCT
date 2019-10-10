#pragma once

#include "team_id.hpp"
#include <array>


namespace solver
{
	struct TeamScore
	{
		int16_t tileScore;
		int16_t regionScore;

		TeamScore()
			: tileScore(0), regionScore(0)
		{

		}
		int16_t getTotalScore()const noexcept
		{
			return tileScore + regionScore;
		}
	};

	struct Score
	{
		std::array<TeamScore, numTeams> teamScores;
	};
}