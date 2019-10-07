#include<string>
#include<vector>

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

