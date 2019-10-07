#include "com_interface.hpp"



namespace solver::com
{
	int ComInterface::getMatchInfo(ReceivedMatchInfo* matchInfo)
	{
		cmdString = "curl -H \"Authorrization: " + tokenString + "\" \"http://localhost:" + portNumString + "/matches\"";
		jsonString = system(cmdString.c_str);
		return 401;
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