#pragma once


namespace solver
{
	constexpr int numTeams = 2;

	enum class TeamID
	{
		red,
		blue,
		numTeamID,
		null = -1
	};

	inline TeamID begin(TeamID)
	{
		return TeamID::red;
	}

	inline TeamID end(TeamID)
	{
		return TeamID::numTeamID;
	}

	inline TeamID operator*(TeamID team_id)
	{
		return team_id;
	}

	inline TeamID operator++(TeamID &team_id)
	{
		return team_id = static_cast<TeamID>(static_cast<int>(team_id) + 1);
	}
}