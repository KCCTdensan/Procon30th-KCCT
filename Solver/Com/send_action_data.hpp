#include<string>
#include<vector>

namespace solver::com
{
	struct SendActionDataOne
	{

		int agentID;
		int dx;
		int dy;
		std::string type;

	};

	struct SendActionData
	{

		std::vector<SendActionDataOne> actions;

	};
}
