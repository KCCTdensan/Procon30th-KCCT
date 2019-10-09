#pragma once

#include "../size.hpp"
#include "../position.hpp"
#include <vector>


namespace solver::simulator
{
	class FieldFlag
	{
		std::vector<std::vector<bool>> flags;

	public:
		FieldFlag(Size fieldSize)
		{
			flags.resize(fieldSize.height);
			for(uint8_t y = 0; y < fieldSize.height; ++y)
			{
				flags[y].resize(fieldSize.width);
				for(uint8_t x = 0; x < fieldSize.width; ++x)
				{
					flags[y][x] = false;
				}
			}
		}
		bool &operator[](Position position)
		{
			return flags[position.y][position.x];
		}
		bool operator[](Position position)const
		{
			return flags[position.y][position.x];
		}
	};
}