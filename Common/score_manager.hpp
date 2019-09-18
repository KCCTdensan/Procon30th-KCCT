#pragma once

#include "score.hpp"


class ScoreManager
{
	Score redScore;
	Score blueScore;

public:
	ScoreManager(const Field &field)
		: redScore(field, TeamRed), blueScore(field, TeamBlue)
	{

	}
	void updateScore()
	{
		redScore.updateScore();
		blueScore.updateScore();
	}
	const Score &getRedScore()const noexcept
	{
		return redScore;
	}
	const Score &getBlueScore()const noexcept
	{
		return blueScore;
	}
};