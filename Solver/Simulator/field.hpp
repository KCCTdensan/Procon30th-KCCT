#pragma once

#include "panel.hpp"
#include "../size.hpp"
#include "../position.hpp"
#include "../field_info.hpp"
#include <vector>


namespace solver
{
	namespace simulator
	{
		class Field
		{
			const Size size;
			std::vector<Panel> panels;

		public:
			Field(const FieldInfo &fieldInfo)
				: size(fieldInfo.getSize())
			{
				for(uint8_t y = 0; y < size.height; ++y)
				{
					for(uint8_t x = 0; x < size.width; ++x)
					{
						Position position;
						position.x = x;
						position.y = y;
						panels.emplace_back(fieldInfo[position]);
					}
				}
			}
			const Panel &operator[](const Position &position)const
			{
				size_t index = static_cast<size_t>(size.width) * position.y + position.x;
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