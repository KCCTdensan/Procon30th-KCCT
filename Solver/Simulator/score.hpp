﻿#pragma once

#include "field.hpp"


namespace solver::simulator
{
	class Score
	{
		const Field &field;
		const TeamID team;
		int16_t tileScore;
		int16_t regionScore;

		void updatePanel(const Panel &panel)noexcept
		{
			if(toTeam(panel.getTileStatus()) == team)
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
		void update()
		{
			tileScore = 0;
			regionScore = 0;
			for(const Panel &panel : field)
			{
				updatePanel(panel);
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
		int16_t getTotalScore()const noexcept
		{
			return tileScore + regionScore;
		}
	};
}