#pragma once

#include "field.hpp"


namespace solver
{
	namespace simulator
	{
		class Score
		{
			const Field &field;
			const TeamID team;
			int16_t tileScore;
			int16_t regionScore;

			void updateScoreOfPanel(const Panel &panel)noexcept
			{
				if(toTeam(panel.getTile()) == team)
				{
					tileScore += panel.getPoint();
				}
				else if(panel.getRegionStatus(team))
				{
					regionScore += panel.getPoint();
				}
			}

		public:
			Score(const Field &field, TeamID team)noexcept
				:field(field), team(team), tileScore(0), regionScore(0)
			{

			}
			void updateScore()
			{
				tileScore = 0;
				regionScore = 0;
				for(const Panel &panel : field)
				{
					updateScoreOfPanel(panel);
				}
			}
			int16_t getTileScore()const noexcept
			{
				return tileScore;
			}
			int16_t getRegionScore()const noexcept
			{
				return regionScore;
			}
			int16_t getAllScore()const noexcept
			{
				return tileScore + regionScore;
			}
		};
	}
}