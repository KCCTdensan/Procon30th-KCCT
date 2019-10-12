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
		std::string hostNameString;
		std::string portNumString;
		std::string tokenString;
		std::string matchIDString;

	public:
		ComInterface(std::string hostNameString,std::string portNumString,std::string matchIDString,std::string tokenString);
		int getMatchInfo(ReceivedMatchInfo* matchInfo);
		int getMatchData(ReceivedMatchData* matchData);
		int sendActionData(SendActionData actionData);
		std::string getPimg();
		std::string getCmdString();

	};
}