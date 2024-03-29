#include<string>
#include<vector>

namespace solver::com
{
	struct ReceivedAgent
	{

		int agentID;
		int x;
		int y;

	};

	struct ReceivedTeam
	{

		std::vector<ReceivedAgent> receivedAgents;
		int areaPoint;
		int teamID;
		int tilePoint;

	};

	struct ReceivedAction
	{

		int agentID;
		int dx; //-1:左
		int dy; //-1:上
		std::string type;
		int apply; //-1:無効 0:競合 1:有効
		int turn; //1ターン目から

	};

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