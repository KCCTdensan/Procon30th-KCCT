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

	inline TeamID toTeam(TileID tile)
	{
		switch(tile)
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