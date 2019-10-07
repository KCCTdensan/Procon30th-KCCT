#include "match_data.hpp"
#include "match_info.hpp"
#include "action_data.hpp"

class ComInterface
{

	int getMatchInfo(MatchInfo* matchInfo);
	int getMatchData(MatchData* matchData);
	int sendActionData(ActionData* actionData);
	int getPimg();

};