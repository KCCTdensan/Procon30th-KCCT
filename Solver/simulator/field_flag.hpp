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
		std::vector<bool>::reference operator[](Position position)
		{
			return flags[position.y][position.x];
		}
		bool operator[](Position position)const
		{
			return flags[position.y][position.x];
		}
		FieldFlag &operator|=(const FieldFlag &flag)
		{
			bool b = false;
			bool &a = b;
			for(uint8_t y = 0; y < flags.size(); ++y)
			{
				for(uint8_t x = 0; x < flags[0].size(); ++x)
				{
					Position position = {x,y};
					(*this)[position] = (*this)[position] || flag[position];
				}
			}
			return *this;
		}
	};
}