#pragma once

#include "../team_id.hpp"
#include "../tile_id.hpp"


namespace solver
{
	namespace simulator
	{
		class Panel
		{
			const int point;
			TileID tileStatus;
			bool regionStatus[numTeams];

		public:
			Panel(int point)noexcept
				: point(point), tileStatus(TileID::none), regionStatus {false}
			{

			}
			int getPoint()const noexcept
			{
				return point;
			}
			void setTile(TileID tile)noexcept
			{
				tileStatus = tile;
				if(tile != TileID::none)
				{
					regionStatus[static_cast<int>(toTeam(tile))] = false;
				}
			}
			void removeTile()noexcept
			{
				tileStatus = TileID::none;
			}
			TileID getTile()const noexcept
			{
				return tileStatus;
			}
			void setRegionStatus(TeamID team, bool isRegion)noexcept
			{
				if(toTeam(tileStatus) != team || !isRegion)
				{
					regionStatus[static_cast<int>(team)] = isRegion;
				}
			}
			bool getRegionStatus(TeamID team)const noexcept
			{
				return regionStatus[static_cast<int>(team)];
			}
		};
	}
}