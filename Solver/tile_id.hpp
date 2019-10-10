#pragma once

#include "team_id.hpp"


namespace solver
{
	enum class TileID
	{
		none,
		red,
		blue
	};

	inline TileID toTile(TeamID team_id)
	{
		switch(team_id)
		{
		case TeamID::red:
			return TileID::red;

		case TeamID::blue:
			return TileID::blue;

		default:
			return TileID::none;
		}
	}

	inline TeamID toTeam(TileID tile_id)
	{
		switch(tile_id)
		{
		case TileID::red:
			return TeamID::red;

		case TileID::blue:
			return TeamID::blue;

		default:
			return TeamID::null;
		}
	}
}