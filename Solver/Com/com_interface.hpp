#include "received_match_data.hpp"
#include "received_match_info.hpp"
#include "send_action_data.hpp"
#include<string>

namespace solver::com
{
class ComInterface
	{
	private:
		std::string cmdString;
		std::string sendDataString;
		std::string portNumString;
		std::string matchIDString;
		std::string tokenString;

	public:
		ComInterface(std::string portNumString,std::string matchIDString,std::string tokenString);
		int getMatchInfo(ReceivedMatchInfo* matchInfo);
		int getMatchData(ReceivedMatchData* matchData);
		int sendActionData(SendActionData actionData);
		int getPimg();
		std::string getCmdString();

	};
}