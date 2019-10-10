#include<iostream>
#include<fstream>
#include<iterator>
#include "com_interface.hpp"
#include "json11.hpp"

namespace solver::com
{
	ComInterface::ComInterface(std::string portNumString, std::string matchIDString, std::string tokenString)
		: portNumString(portNumString),matchIDString(matchIDString),tokenString(tokenString)
	{

	}

	int ComInterface::getMatchInfo(ReceivedMatchInfo* receivedMatchInfo)
	{
		cmdString = "curl -H \"Authorization:" + tokenString + "\" \"http://localhost:" + portNumString + "/matches\" > ./match_info.json";
		//std::cout << "cmdStr: " << cmdString << std::endl;
		system(cmdString.c_str());

		std::ifstream ifstrm("./match_info.json");
		std::string jsonString((std::istreambuf_iterator<char>(ifstrm)),std::istreambuf_iterator<char>());
		std::cout << "jsonstr : " << jsonString << std::endl;
		
		std::string errString;
		auto matchInfoJson = json11::Json::parse(jsonString,errString);
		auto matchInfos = matchInfoJson.array_items();
		
		int i = 0;
		for(auto &info : matchInfos)
		{
			ReceivedMatchInfoOne receivedMatchInfoOne;
			std::cout << i << " : " << info["id"].int_value() << std::endl;
			receivedMatchInfoOne.id = info["id"].int_value();
			receivedMatchInfoOne.intervalMillis = info["intervalMillis"].int_value();
			receivedMatchInfoOne.matchTo = info["matchTo"].string_value();
			receivedMatchInfoOne.teamID = info["teamID"].int_value();
			receivedMatchInfoOne.turnMillis = info["turnMillis"].int_value();
			receivedMatchInfoOne.turns = info["turns"].int_value();
			receivedMatchInfo->MatchesInfo.emplace_back(receivedMatchInfoOne);
			i++;

		}
		return 200;
	}

	int ComInterface::getMatchData(ReceivedMatchData* receivedMatchData)
	{
		cmdString = "curl -H \"Authorrization: " + tokenString + "\" \"http://localhost:" + portNumString + "/matches/" + matchIDString + "\" > ./match_data.json";
		system(cmdString.c_str());

		std::ifstream ifstrm("./match_data.json");
		std::string jsonString((std::istreambuf_iterator<char>(ifstrm)), std::istreambuf_iterator<char>());
		std::cout << "jsonstr : " << jsonString << std::endl;

		std::string errString;
		auto matchDataJson = json11::Json::parse(jsonString, errString);
		auto actions = matchDataJson["actions"].array_items();

		int i = 0;
		for (auto& data : actions)
		{
			ReceivedAction receivedAction;
			std::cout << i << " : " << data["agentID"].int_value() << std::endl;
			receivedAction.agentID = actions["agentID"].int_value();
			receivedAction.dx = actions["dx"].int_value();
			receivedAction.dy = actions["dy"].int_value();
			receivedAction.type = actions["type"].string_value();
			receivedAction.apply = actions["apply"].int_value();
			receivedAction.turn = actions["turn"].int_value();
			receivedMatchData->receivedActions.emplace_back(receivedAction);
			i++;

		}
		receivedMatchData->height = matchDataJson["height"].int_value();
		auto manyPoint = matchDataJson["points"].array_items();
		for (auto points : manyPoint)
		{
			std::vector<int> integerPoints;
			auto pointsArray = points.array_items();
			for (auto point : pointsArray)
			{
				integerPoints
			}
		}
		return 200;
	}

	int ComInterface::sendActionData(SendActionData actionData)
	{
		cmdString = "curl -H \"Authorization: "+tokenString+"\" -H \"Content-Type: application/json\" -X POST \"http://localhost:" + tokenString + "/matches/1/action\" -d \""+sendDataString+" > ./match_info.json";
		//std::string jsonString = system(cmdString.c_str());
		return 401;
	}

	int ComInterface::getPimg()
	{
		cmdString = "curl - H \"Authorization: "+tokenString+"\" \"http://localhost:"+portNumString+"/matches > ./match_info.json";
		//std::string jsonString = system(cmdString.c_str());
		return 401;
	}

	std::string ComInterface::getCmdString() 
	{
		return cmdString;
	}
};