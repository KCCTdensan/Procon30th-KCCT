#pragma once

#include "team.hpp"


enum TileState
{
	NoTile,
	RedTile,
	BlueTile
};

TeamID toTeam(TileState tile)
{
	switch(tile)
	{
	case RedTile:
		return TeamRed;

	case BlueTile:
		return TeamBlue;

	default:
		return TeamNull;
	}
}