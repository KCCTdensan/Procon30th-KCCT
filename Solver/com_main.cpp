#include<iostream>
#include<string>
#include<vector>
#include "Com/com_interface.hpp"
#include<windows.h>
#include<random>

int main()
{
	std::string hostName;
	std::string portNum;
	std::string token;
	std::string matchID;
	int enemyTeamID;
	int turnMillis;
	int teamNum = 0;

	hostName = "10.10.52.252";
	portNum = "80";
	token = "d55101d94c146f52bb03345bba0c58c01435cd0314a95518eeb4518f182c774a"

	std::cout << "matchID enemyID turnMillis";
	std::cin >> matchID >> enemyTeamID >> turnMillis;

	solver::com::ComInterface comInterFace(hostName,portNum,matchID,token);
	solver::com::ReceivedMatchInfo receivedMatchInfo;
	solver::com::ReceivedMatchData receivedMatchData;
	solver::com::SendActionData sendActionData;

	system("chcp 65001"); //コマンドプロンプトの文字コードページをUTF-8に設定

	//getPing
	std::cout << comInterFace.getPimg() << std::endl;

	//試合情報取得
	std::cout << comInterFace.getMatchInfo(&receivedMatchInfo) << std::endl;

	//試合情報表示
	for (solver::com::ReceivedMatchInfoOne receivedMatchInfoOne : receivedMatchInfo.MatchesInfo)
	{
		std::cout << "id : " << receivedMatchInfoOne.id << std::endl;
		std::cout << "intervalMillis : " << receivedMatchInfoOne.intervalMillis << std::endl;
		std::cout << "matchTo : " << receivedMatchInfoOne.matchTo << std::endl;
		std::cout << "teamID : " << receivedMatchInfoOne.teamID << std::endl;
		std::cout << "turnMillis : " << receivedMatchInfoOne.turnMillis << std::endl;
		std::cout << "turns : " << receivedMatchInfoOne.turns << std::endl;
	}

	//試合データ取得
	std::cout << comInterFace.getMatchData(&receivedMatchData) << std::endl;

	//送信用agent配列作成
	int teamN = 0;
	for (solver::com::ReceivedTeam team : receivedMatchData.teams)
	{
		if (team.teamID != enemyTeamID)
		{
			teamNum = teamN;
			for (solver::com::ReceivedAgent receivedAgent : team.receivedAgents)
			{
				std::cout << "Agent:" << receivedAgent.agentID << std::endl;
				solver::com::SendActionDataOne sendActionDataOne;
				sendActionDataOne.agentID = receivedAgent.agentID;
				sendActionData.actions.emplace_back(sendActionDataOne);
			}
		}
		teamN++;
	}

	//行動更新
	for(int i=0;i<10000;i++)
	{
		while(1)
		{
			if (receivedMatchData.turn > i)break;
			Sleep(turnMillis / 3);
			std::cout << "turn:" << i << std::endl;
			for (int agentNum = 0; agentNum < sendActionData.actions.size(); agentNum++)
			{
				//行動代入
				std::cout << sendActionData.actions[agentNum].agentID << ":" << std::endl;
				sendActionData.actions[agentNum].dx = std::rand()%2;
				if (std::rand() % 2)sendActionData.actions[agentNum].dx *= -1;
				sendActionData.actions[agentNum].dy = std::rand() % 2;
				if (std::rand() % 2)sendActionData.actions[agentNum].dx *= -1;
				sendActionData.actions[agentNum].type = "move";
				//std::cin >> sendActionData.actions[agentNum].dx >> sendActionData.actions[agentNum].dy >> sendActionData.actions[agentNum].type;

				//move or remove
				for (solver::com::ReceivedAgent agent : receivedMatchData.teams[teamNum].receivedAgents)
				{
					if (agent.agentID == sendActionData.actions[agentNum].agentID)
					{
						/*
						if (receivedMatchData.tiled[agent.x + sendActionData.actions[agentNum].dx][agent.y + sendActionData.actions[agentNum].dy] == enemyTeamID)
						{
							sendActionData.actions[agentNum].type = "remove";
						}
						*/

					}
				}
				std::cout << "dx:" << sendActionData.actions[agentNum].dx << " dy:" << sendActionData.actions[agentNum].dy <<std::endl;
				std::cout << "type:" << sendActionData.actions[agentNum].type << std::endl;
			}
			std::cout << comInterFace.sendActionData(sendActionData) << std::endl;
			std::cout << comInterFace.getMatchData(&receivedMatchData) << std::endl;
		}
	}

	//std::cout << receivedMatchInfo.MatchesInfo[0].id << std::endl;
	
	//std::cout << comInterFace.getCmdString() << std::endl;
	//system(comInterFace.getCmdString().c_str());
	//system("curl -H \"Authorization: procon30_example_token\" \"http://localhost:3000/matches\"");
	
	Sleep(3*1000);
	return 0;
}
