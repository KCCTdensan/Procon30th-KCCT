#include "com_interface.hpp"
#include "json11.hpp"

namespace solver::com
{
	ComInterface::ComInterface(std::string portNumString, std::string matchIDString, std::string tokenString)
		: portNumString(portNumString),matchIDString(matchIDString),tokenString(tokenString)
	{

	}

	int ComInterface::getMatchInfo(ReceivedMatchInfo* matchInfo)
	{
		cmdString = "curl -H \"Authorrization: " + tokenString + "\" \"http://localhost:" + portNumString + "/matches\"";
		if (cmdString == "401")return 401;
		jsonString = system(cmdString.c_str);
		std::string errString;
		auto matchInfoJson = json11::Json::parse(jsonString,errString);
		auto matchInfos = matchInfoJson.array_items();
		int i = 0;
		for(auto &info : matchInfos)
		{

			matchInfo->MatchesInfo[i].id = info["id"].int_value();
			matchInfo->MatchesInfo[i].intervalMillis = info["intervalMillis"].int_value();
			matchInfo->MatchesInfo[i].matchTo = info["matchTo"].string_value();
			matchInfo->MatchesInfo[i].teamID = info["teamID"].int_value();
			matchInfo->MatchesInfo[i].turnMillis = info["turnMillis"].int_value();
			matchInfo->MatchesInfo[i].turns = info["turns"].int_value();
			i++;

		}
		return 200;
	}

	int ComInterface::getMatchData(ReceivedMatchData* matchData)
	{
		cmdString = "curl -H \"Authorrization: " + tokenString + "\" \"http://localhost:" + portNumString + "/matches/" + matchIDString + "\"";
		jsonString = system(cmdString.c_str);
		return 401;
	}

	int ComInterface::sendActionData(SendActionData actionData)
	{
		cmdString = "curl -H \"Authorization: "+tokenString+"\" -H \"Content-Type: application/json\" -X POST \"http://localhost:" + tokenString + "/matches/1/action\" -d \""+sendDataString;
		jsonString = system(cmdString.c_str);
		return 401;
	}

	int ComInterface::getPimg()
	{
		cmdString = "curl - H \"Authorization: "+tokenString+"\" \"http://localhost:"+portNumString+"/matches";
		jsonString = system(cmdString.c_str);
		return 401;
	}
};