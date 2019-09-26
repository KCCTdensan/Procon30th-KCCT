#pragma once

#include "panel.hpp"
#include "../size.hpp"
#include "../position.hpp"
#include <vector>


namespace solver
{
	namespace simulator
	{
		struct FieldInfo
		{
			Size size;
			std::vector<std::vector<int>> panelPoints;
		};

		class Field
		{
			const Size size;
			std::vector<Panel> panels;

		public:
			Field(const FieldInfo &fieldInfo)
				: size(fieldInfo.size)
			{
				for(size_t h = 0; h < size.height; ++h)
				{
					for(size_t w = 0; w < size.width; ++w)
					{
						panels.emplace_back(fieldInfo.panelPoints[h][w]);
					}
				}
			}
			const Panel &operator[](Position position)const
			{
				return panels[size.width * position.y + position.x];
			}
			const Size getSize()const noexcept
			{
				return size;
			}
			auto begin()const noexcept
			{
				return panels.begin();
			}
			auto end()const noexcept
			{
				return panels.end();
			}
		};
	}
}