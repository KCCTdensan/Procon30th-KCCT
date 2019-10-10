#pragma once

#include "size.hpp"
#include <vector>


namespace solver
{
	class FieldInfo
	{
		Size size;
		std::vector<std::vector<int8_t>> panelPoints;

	public:
		FieldInfo()
			: size {0, 0}
		{

		}
		void setSize(Size size)
		{
			this->size = size;
			panelPoints.resize(size.height);
			for(auto &line : panelPoints)
			{
				line.resize(size.width);
			}
		}
		Size getSize()const
		{
			return size;
		}
		int8_t &operator[](Position position)
		{
			return panelPoints[position.y][position.x];
		}
		const int8_t &operator[](Position position)const
		{
			return panelPoints[position.y][position.x];
		}
	};
}