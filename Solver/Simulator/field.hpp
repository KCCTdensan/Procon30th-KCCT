#pragma once

#include "panel.hpp"
#include "../size.hpp"
#include "../position.hpp"
#include "../field_info.hpp"
#include "stage_flag.hpp"
#include <vector>


namespace solver::simulator
{
	class Field
	{
		const Size size;
		std::vector<Panel> panels;

		Panel &operator[](Position position)
		{
			const size_t index = static_cast<size_t>(size.width) *position.y + position.x;
			return panels[index];
		}
		int checkRegionPanel(Position position, TileID tile, FieldFlag<int8_t> &fieldFlag)
		{
			//フィールドの範囲外の場合
			if(!isPositionInField(position, size))return -1;
			//自チームのタイルが存在する場合
			if((*this)[position].getTileStatus() == tile)return 0;
			//チェック済みの場合
			if(fieldFlag[position] != 0)return 0;
			fieldFlag[position] = 1;

			int retL = checkRegionPanel(movedPosition(position, DirectionID::left), tile, fieldFlag);
			if(retL == -1)return -1;
			int retT = checkRegionPanel(movedPosition(position, DirectionID::top), tile, fieldFlag);
			if(retT == -1)return -1;
			int retR = checkRegionPanel(movedPosition(position, DirectionID::right), tile, fieldFlag);
			if(retR == -1)return -1;
			int retB = checkRegionPanel(movedPosition(position, DirectionID::bottom), tile, fieldFlag);
			if(retB == -1)return -1;

			return 1;
		}
		void setRegionPanel(Position position, TileID tile, bool isRegionPanel, FieldFlag<int8_t> &fieldFlag)
		{
			//フィールドの範囲外の場合
			if(!isPositionInField(position, size))return;
			//自チームのタイルが存在する場合
			if((*this)[position].getTileStatus() == tile)return;
			//チェック済みの場合
			if(fieldFlag[position] == 2)return;
			fieldFlag[position] = 2;
			(*this)[position].setRegionStatus(toTeam(tile), isRegionPanel);
			setRegionPanel(movedPosition(position, DirectionID::left), tile, isRegionPanel, fieldFlag);
			setRegionPanel(movedPosition(position, DirectionID::top), tile, isRegionPanel, fieldFlag);
			setRegionPanel(movedPosition(position, DirectionID::right), tile, isRegionPanel, fieldFlag);
			setRegionPanel(movedPosition(position, DirectionID::bottom), tile, isRegionPanel, fieldFlag);
		}
		void updateRegionPanelStart(Position position, TileID tile, FieldFlag<int8_t> &fieldFlag)
		{
			const int ret = checkRegionPanel(position, tile, fieldFlag);
			if(ret == 0)
			{
				return;
			}
			const bool isRegionPanel = ret == 1;
			setRegionPanel(position, tile, isRegionPanel, fieldFlag);
		}
		void updateRegionPanel(Position startPosition, TileID tile)
		{
			FieldFlag<int8_t> fieldFlag(size);
			updateRegionPanelStart(movedPosition(startPosition, DirectionID::left), tile, fieldFlag);
			updateRegionPanelStart(movedPosition(startPosition, DirectionID::top), tile, fieldFlag);
			updateRegionPanelStart(movedPosition(startPosition, DirectionID::right), tile, fieldFlag);
			updateRegionPanelStart(movedPosition(startPosition, DirectionID::bottom), tile, fieldFlag);
		}

	public:
		Field(const FieldInfo &fieldInfo)
			: size(fieldInfo.getSize())
		{
			for(uint8_t y = 0; y < size.height; ++y)
			{
				for(uint8_t x = 0; x < size.width; ++x)
				{
					const Position position(x, y);
					panels.emplace_back(fieldInfo[position]);
				}
			}
		}
		const Panel &operator[](Position position)const
		{
			const size_t index = static_cast<size_t>(size.width) *position.y + position.x;
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
		void setTileOnPanel(Position panelPosition, TileID tile)
		{
			(*this)[panelPosition].setTile(tile);
			for(int t = 0; t < numTeams; ++t)
			{
				updateRegionPanel(panelPosition, toTile(static_cast<TeamID>(t)));
			}
		}
		void removeTileOnPanel(Position panelPosition)
		{
			(*this)[panelPosition].removeTile();
			for(int t = 0; t < numTeams; ++t)
			{
				updateRegionPanel(panelPosition, toTile(static_cast<TeamID>(t)));
			}
		}
	};
}