#pragma once

#include <array>
#include <numeric>


namespace solver
{
	int getRandomValue(int minValue, int maxValue);

	template<int size>
	int probability(const std::array<unsigned, size> &evaluationValue)
	{
		const unsigned denominator = std::reduce(evaluationValue.begin(), evaluationValue.end());
		unsigned randomValue = getRandomValue(0, denominator - 1);
		for(int i = 0; i < size - 1; ++i)
		{
			if(randomValue < evaluationValue[i])
			{
				return i;
			}
			randomValue -= evaluationValue[i];
		}
		return size - 1;
	}
}