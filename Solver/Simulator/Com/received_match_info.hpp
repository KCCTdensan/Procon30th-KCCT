#include<string>
#include<vector>

namespace solver::com
{
	struct ReceivedMatchInfoOne
	{

		int id;
		int intervalMillis;
		std::string matchTo;
		int teamID;
		int turnMillis;
		int turns;

	};

	struct ReceivedMatchInfo
	{

		std::vector<ReceivedMatchInfoOne> MatchsInfo;

	};
}