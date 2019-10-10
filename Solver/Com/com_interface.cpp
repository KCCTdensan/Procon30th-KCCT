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
		//cmdString = "curl -H \"Authorization: " + tokenString + "\" \"http://localhost:" + portNumString + "/matches/" + matchIDString + "\" > ./match_data.json";
		//system(cmdString.c_str());

		std::ifstream ifstrm("./match_data.json");
		std::string jsonString((std::istreambuf_iterator<char>(ifstrm)), std::istreambuf_iterator<char>());
		std::cout << "jsonstr : " << jsonString << std::endl;

		std::string errString;
		auto matchDataJson = json11::Json::parse(jsonString, errString);
		auto actions = matchDataJson["actions"].array_items();

		receivedMatchData->turn = matchDataJson["turn"].int_value();
		receivedMatchData->startedAtUnixTime = matchDataJson["startedAtUnixTime"].int_value();
		receivedMatchData->width = matchDataJson["width"].int_value();
		receivedMatchData->height = matchDataJson["height"].int_value();
		for (auto action : actions)
		{
			ReceivedAction receivedAction;
			receivedAction.agentID = action["agentID"].int_value();
			receivedAction.dx = action["dx"].int_value();
			receivedAction.dy = action["dy"].int_value();
			receivedAction.type = action["type"].string_value();
			receivedAction.apply = action["apply"].int_value();
			receivedAction.turn = action["turn"].int_value();
			receivedMatchData->receivedActions.emplace_back(receivedAction);
		}
		for (auto team : matchDataJson["teams"].array_items())
		{
			ReceivedTeam receivedTeam;
			for (auto agent : team["agents"].array_items())
			{
				ReceivedAgent receivedAgent;
				receivedAgent.agentID = agent["agentID"].int_value();
				receivedAgent.x = agent["x"].int_value();
				receivedAgent.y = agent["y"].int_value();
				receivedTeam.receivedAgents.emplace_back(receivedAgent);
			}
			receivedTeam.areaPoint = team["areaPoint"].int_value();
			receivedTeam.teamID = team["teamID"].int_value();
			receivedTeam.tilePoint = team["tilePoint"].int_value();
			receivedMatchData->teams.emplace_back(receivedTeam);
		}
		for (auto points : matchDataJson["points"].array_items())
		{
			std::vector<int> integerPoints;
			for (auto point : points.array_items())
			{
				integerPoints.emplace_back(point.int_value());
			}
			receivedMatchData->points.emplace_back(integerPoints);
		}
		for (auto tileds : matchDataJson["tiled"].array_items())
		{
			std::vector<int>integerTileds;
			for (auto tiled : tileds.array_items())
			{
				integerTileds.emplace_back(tiled.int_value());
			}
			receivedMatchData->tiled.emplace_back(integerTileds);
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