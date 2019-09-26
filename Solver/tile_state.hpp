#pragma once

#include "team.hpp"


namespace solver
{
	enum class TileID
	{
		none,
		red,
		blue
	};

	TeamID toTeam(TileID tile)
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