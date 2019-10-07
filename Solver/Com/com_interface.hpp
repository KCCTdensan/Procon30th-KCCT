#include "match_data.hpp"
#include "match_info.hpp"
#include "action_data.hpp"
#include<string>

class ComInterface
{
private:
	std::string cmdString;
	std::string jsonString;
	std::string 

	int getMatchInfo(MatchInfo* matchInfo);
	int getMatchData(MatchData* matchData);
	int sendActionData(ActionData actionData);
	int getPimg();

};