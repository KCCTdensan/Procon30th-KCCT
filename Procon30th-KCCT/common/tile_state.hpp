#pragma once

#include "team.hpp"


enum class TileState
{
	NoTile,
	RedTile,
	BlueTile
};

TeamID toTeam(TileState tile)
{
	switch(tile)
	{
	case TileState::RedTile:
		return TeamID::TeamRed;

	case TileState::BlueTile:
		return TeamID::TeamBlue;

	default:
		return TeamID::TeamNull;
	}
}