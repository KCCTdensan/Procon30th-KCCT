#include<iostream>
#include<string>
#include "Com/com_interface.hpp"
#include<windows.h>

int main()
{
	solver::com::ComInterface comInterFace("kd-D-004","3000","6","procon30_example_token");
	solver::com::ReceivedMatchInfo receivedMatchInfo;
	solver::com::ReceivedMatchData receivedMatchData;
	solver::com::SendActionData sendActionData;

	system("chcp 65001"); //�R�}���h�v�����v�g�̕����R�[�h�y�[�W��UTF-8�ɐݒ�

	//�������擾
	std::cout << comInterFace.getMatchInfo(&receivedMatchInfo) << std::endl;
	for (solver::com::ReceivedMatchInfoOne receivedMatchInfoOne : receivedMatchInfo.MatchesInfo)
	{
		std::cout << "id : " << receivedMatchInfoOne.id << std::endl;
		std::cout << "intervalMillis : " << receivedMatchInfoOne.intervalMillis << std::endl;
		std::cout << "matchTo : " << receivedMatchInfoOne.matchTo << std::endl;
		std::cout << "teamID : " << receivedMatchInfoOne.teamID << std::endl;
		std::cout << "turnMillis : " << receivedMatchInfoOne.turnMillis << std::endl;
		std::cout << "turns : " << receivedMatchInfoOne.turns << std::endl;
	}
	
	//�����f�[�^�擾
	std::cout << comInterFace.getMatchData(&receivedMatchData) << std::endl;

	//�s���X�V
	solver::com::SendActionDataOne sendActionData1;
	solver::com::SendActionDataOne sendActionData2;
	sendActionData1 = { 9,1,1,"move" };
	sendActionData2 = { 10,1,1,"move" };
	sendActionData.actions.emplace_back(sendActionData1);
	sendActionData.actions.emplace_back(sendActionData2);

	std::cout << comInterFace.sendActionData(sendActionData) << std::endl;
	//std::cout << receivedMatchInfo.MatchesInfo[0].id << std::endl;
	
	//std::cout << comInterFace.getCmdString() << std::endl;
	//system(comInterFace.getCmdString().c_str());
	//system("curl -H \"Authorization: procon30_example_token\" \"http://localhost:3000/matches\"");
	
	Sleep(3*1000);
	return 0;
}
