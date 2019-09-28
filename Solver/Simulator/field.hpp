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
			std::vector<std::vector<int8_t>> panelPoints;
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
			const Panel &operator[](const Position &position)const
			{
				size_t index = static_cast<size_t>(size.width) *position.y + position.x;
				return panels[index];
			}
			const Size getSize()const noexcept
			{
				return size;
			}
			auto begin()noexcept
			{
				return panels.begin();
			}
			auto begin()const noexcept
			{
				return panels.begin();
			}
			auto end()noexcept
			{
				return panels.end();
			}
			auto end()const noexcept
			{
				return panels.end();
			}
		};
	}
}