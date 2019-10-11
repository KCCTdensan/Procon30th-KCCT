#pragma once

#include "field.hpp"


namespace solver::simulator
{
	class ScoreUpdater
	{
		const Field &field;
		const TeamID team;
		TeamScore score;

		void updatePanel(const Panel &panel)noexcept
		{
			if(toTeam(panel.getTileStatus()) == team)
			{
				score.tileScore += panel.getPoint();
			}
			else if(panel.getRegionStatus(team))
			{
				score.regionScore += std::abs(panel.getPoint());
			}
		}

	public:
		ScoreUpdater(const Field &field, TeamID team)noexcept
			:field(field), team(team)
		{

		}
		void update()
		{
			score.tileScore = 0;
			score.regionScore = 0;
			for(const Panel &panel : field)
			{
				updatePanel(panel);
			}
		}
		TeamScore getScore()const noexcept
		{
			return score;
		}
		int16_t getTileScore()const noexcept
		{
			return score.tileScore;
		}
		int16_t getRegionScore()const noexcept
		{
			return score.regionScore;
		}
		int16_t getTotalScore()const noexcept
		{
			return score.getTotalScore();
		}
	};
}