#include "random.hpp"
#include <random>


namespace solver
{
	std::random_device randomDevice;
	std::mt19937 randomMT(randomDevice());

	int getRandomValue(int minValue, int maxValue)
	{
		if(minValue == maxValue)
		{
			return minValue;
		}
		if(minValue > maxValue)
		{
			std::swap(minValue, maxValue);
		}
		return randomMT() % (maxValue - minValue + 1) + minValue;
	}
}