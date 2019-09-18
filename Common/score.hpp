#pragma once

#include "field.hpp"


class Score
{
	const Field &field;
	const TeamID team;
	int tileScore;
	int regionScore;

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
	int getTileScore()const noexcept
	{
		return tileScore;
	}
	int getRegionScore()const noexcept
	{
		return regionScore;
	}
	int getAllScore()const noexcept
	{
		return tileScore + regionScore;
	}
};