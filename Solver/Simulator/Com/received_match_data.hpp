#include<string>
#include<vector>

namespace solver::com
{
	struct ReceivedAgent
	{

		int agentID;
		int x;
		int y;

	}

	struct ReceivedTeam
	{

		std::vector<ReceivedAgent> receivedAgents;
		int areaPoint;
		int teamID;
		int tilePoint;

	}

	struct ReceivedAction
	{

		int agentID;
		int dx;
		int dy;
		std::string type;
		int apply;
		int turn;

	}

	struct ReceivedMatchData
	{

		std::vector<ReceivedAction> receivedActions;
		int height;
		std::vector<std::vector<int>> points;
		int startedAtUnixTime;
		std::vector<ReceivedTeam> teams;
		std::vector<std::vector<int>> tiled;
		int turn;
		int width;

	};

}