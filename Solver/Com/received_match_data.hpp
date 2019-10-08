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
		int dx; //-1:¶
		int dy; //-1:ã
		std::string type;
		int apply; //-1:–³Œø 0:‹£‡ 1:—LŒø
		int turn; //1ƒ^[ƒ“–Ú‚©‚ç

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