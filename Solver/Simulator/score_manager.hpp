#pragma once

#include "score.hpp"


namespace solver
{
	namespace simulator
	{
		class ScoreManager
		{
			Score redScore;
			Score blueScore;

		public:
			ScoreManager(const Field &field)
				: redScore(field, TeamID::red), blueScore(field, TeamID::blue)
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
	}
}