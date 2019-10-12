#pragma once

#include "../team_id.hpp"
#include "../tile_id.hpp"


namespace solver::simulator
{
	class Panel
	{
		const int8_t point;
		TileID tileStatus;
		std::array<bool, numTeams> regionStatus;

	public:
		Panel(int8_t point)noexcept
			: point(point), tileStatus(TileID::none)
		{
			std::fill(regionStatus.begin(), regionStatus.end(), false);
		}
		int8_t getPoint()const noexcept
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
		TileID getTileStatus()const noexcept
		{
			return tileStatus;
		}
		void setRegionStatus(TeamID team, bool isRegion)noexcept
		{
			if(tileStatus != toTile(team) || !isRegion)
			{
				regionStatus[static_cast<size_t>(team)] = isRegion;
			}
		}
		bool getRegionStatus(TeamID team)const noexcept
		{
			return regionStatus[static_cast<size_t>(team)];
		}
	};
}