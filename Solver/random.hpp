#pragma once

#include <array>
#include <numeric>


namespace solver
{
	int getRandomValue(int minValue, int maxValue);

	template<size_t size>
	int probability(const std::array<float, size> &evaluationValue)
	{
		float denominator = std::reduce(evaluationValue.begin(), evaluationValue.end());
		float randomValue = getRandomValue(0, static_cast<int>(denominator * 64)) / 64.0f;
		for(size_t i = 0; i < size - 1; ++i)
		{
			if(randomValue < evaluationValue[i])
			{
				return evaluationValue[i];
			}
			randomValue -= evaluationValue[i];
		}
		return size - 1;
	}
}