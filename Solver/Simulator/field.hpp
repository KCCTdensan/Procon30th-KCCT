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
			size_t index = static_cast<size_t>(size.width) *position.y + position.x;
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

			int retL = checkRegionPanel(movedPosition(position, ActionID::left), tile, fieldFlag);
			if(retL == -1)return -1;
			int retT = checkRegionPanel(movedPosition(position, ActionID::top), tile, fieldFlag);
			if(retT == -1)return -1;
			int retR = checkRegionPanel(movedPosition(position, ActionID::right), tile, fieldFlag);
			if(retR == -1)return -1;
			int retB = checkRegionPanel(movedPosition(position, ActionID::bottom), tile, fieldFlag);
			if(retB == -1)return -1;

			return 1;
		}
		void setRegionPanel(Position position, TileID tile, bool isRegionPanel, FieldFlag<int8_t> &fieldFlag)
		{
			//フィールドの範囲外の場合
			if(!isPositionInField(position, size))return;
			if(fieldFlag[position] != 1)return;
			fieldFlag[position] = 2;
			(*this)[position].setRegionStatus(toTeam(tile), isRegionPanel);
			setRegionPanel(movedPosition(position, ActionID::left), tile, isRegionPanel, fieldFlag);
			setRegionPanel(movedPosition(position, ActionID::top), tile, isRegionPanel, fieldFlag);
			setRegionPanel(movedPosition(position, ActionID::right), tile, isRegionPanel, fieldFlag);
			setRegionPanel(movedPosition(position, ActionID::bottom), tile, isRegionPanel, fieldFlag);
		}
		void updateRegionPanelStart(Position position, TileID tile, FieldFlag<int8_t> &fieldFlag)
		{
			int ret = checkRegionPanel(position, tile, fieldFlag);
			if(ret == 0)
			{
				return;
			}
			bool isRegionPanel = ret == 1;
			setRegionPanel(position, tile, isRegionPanel, fieldFlag);
		}
		void updateRegionPanel(Position startPosition, TileID tile)
		{
			FieldFlag<int8_t> fieldFlag(size);
			updateRegionPanelStart(movedPosition(startPosition, ActionID::left), tile, fieldFlag);
			updateRegionPanelStart(movedPosition(startPosition, ActionID::top), tile, fieldFlag);
			updateRegionPanelStart(movedPosition(startPosition, ActionID::right), tile, fieldFlag);
			updateRegionPanelStart(movedPosition(startPosition, ActionID::bottom), tile, fieldFlag);
		}

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
		const Panel &operator[](Position position)const
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
		void actPanel(Position position, TeamID agentTeam)
		{
			TileID panelTileStatus = (*this)[position].getTileStatus();
			if(panelTileStatus == TileID::none)
			{
				(*this)[position].setTile(toTile(agentTeam));
				//
				return;
			}
			if(panelTileStatus != toTile(agentTeam))
			{
				(*this)[position].removeTile();
				//
			}
		}
	};
}