#include<string>
#include<vector>


namespace solver::com
{
	struct SendActionDataOne
	{
		int aentID;
		int dx;
		int dy;
		std::string type;
	};

	struct SendActionData
	{
		std::vector<SendActionDataOne> actions;
	};
}
