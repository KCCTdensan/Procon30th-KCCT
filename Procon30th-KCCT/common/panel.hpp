#pragma once

#include "team.hpp"
#include "tile_state.hpp"


class Panel
{
	const int point;
	TileState tile;
	bool regionStatus[numTeams];

public:
	Panel(int point)noexcept
		: point(point), tile(NoTile), regionStatus{false}
	{

	}
	int getPoint()const noexcept
	{
		return point;
	}
	void setTile(TileState tile)noexcept
	{
		this->tile = tile;
		if(tile != NoTile)
		{
			regionStatus[toTeam(tile)] = false;
		}
	}
	void removeTile()noexcept
	{
		tile = NoTile;
	}
	TileState getTile()const noexcept
	{
		return tile;
	}
	void setRegionStatus(TeamID team, bool isRegion)noexcept
	{
		if(toTeam(tile) != team || !isRegion)
		{
			regionStatus[team] = isRegion;
		}
	}
	bool getRegionStatus(TeamID team)const noexcept
	{
		return regionStatus[team];
	}
};