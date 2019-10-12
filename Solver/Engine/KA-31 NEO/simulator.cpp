#include "simulator.hpp"
#include "../../random.hpp"


namespace solver::engine::ka31neo
{
	ActionID Simulator::decideAgentCommand(const StageInterface &stage, TeamID team, uint8_t agentNo)const
	{		
		std::array<float, numActionID> actionEvaluationValues;
		Position agentPosition = stage.getAgentPosition(team, agentNo);
		for(ActionID action : ActionID())
		{
			Position nextPosition = movedPosition(agentPosition, action);
			if(!isPositionInField(nextPosition, stage.getFieldSize()))
			{
				continue;
			}
			int8_t panelPoint = stage.getPanelPoint(nextPosition);
			TileID panelTileStatus = stage.getPanelTileStatus(nextPosition);
			actionEvaluationValues[static_cast<size_t>(action)] = panelTileStatus == toTile(team) ? 0.0f : exp(panelPoint);
		}
		return static_cast<ActionID>(probability(actionEvaluationValues));
		/*
		ActionID action;
		do
		{
			action = static_cast<ActionID>(getRandomValue(1, numActionID));
		}
		while(!stage.canAgentAct(team, agentNo, action));
		return action;
		*/
	}

	StageCommand Simulator::decideCommand(const StageInterface &stage)const
	{
		StageCommand command(stage.getNumAgents());
		for(TeamID team : TeamID())
		{
			for(uint8_t i = 0; i < stage.getNumAgents(); ++i)
			{
				command.teamCommands[static_cast<size_t>(team)].commands[i] = decideAgentCommand(stage, team, i);
			}
		}
		return command;
	}

	float Simulator::calculateReward(const Score &score)const
	{
		std::array<int16_t, numTeams> totalScores;
		for(TeamID team : TeamID())
		{
			totalScores[static_cast<size_t>(team)] = score.teamScores[static_cast<size_t>(team)].getTotalScore();
		}
		if(totalScores[static_cast<size_t>(TeamID::red)] != totalScores[static_cast<size_t>(TeamID::blue)])//全体スコアが違っていた場合
		{
			//全体スコアを比較
			float redEvaluationValue = std::tanh(static_cast<float>(totalScores[static_cast<size_t>(TeamID::red)] - totalScores[static_cast<size_t>(TeamID::blue)]) * 0.1f);
			switch(teamID)
			{
			case TeamID::red:
				return redEvaluationValue;

			case TeamID::blue:
				return -redEvaluationValue;
			}
		}
		else//全体スコアが等しい場合
		{
			//タイルスコアを比較
			float redEvaluationValue = std::tanh(static_cast<float>(score.teamScores[static_cast<size_t>(TeamID::red)].tileScore - score.teamScores[static_cast<size_t>(TeamID::blue)].tileScore) * 0.1f);
			switch(teamID)
			{
			case TeamID::red:
				return redEvaluationValue;

			case TeamID::blue:
				return -redEvaluationValue;
			}
		}
		return 0.0f;
	}

	Simulator::Simulator(TeamID teamID, int8_t agentNo, const StageInterface &currentStage)
		: teamID(teamID), agentNo(agentNo), currentStage(currentStage)
	{

	}

	float Simulator::rollout()const
	{
		StageInterface &stage = *currentStage.copy();
		std::queue<ActionID> commandList = this->commandList;
		while(commandList.size() != 0)
		{
			StageCommand command = decideCommand(stage);
			command.teamCommands[static_cast<size_t>(teamID)].commands[agentNo] = commandList.front();
			commandList.pop();
			stage.act(command);
		}
		for(uint8_t i = 0; i < stage.getNumRemainingTurns() && i < 10; ++i)
		{
			StageCommand command = decideCommand(stage);
			stage.act(command);
		}
		Score finalScore = stage.getScore();
		stage.destroy();
		return calculateReward(finalScore);
	}

	bool Simulator::canAct(ActionID actionID)const noexcept
	{
		return currentStage.canAgentAct(teamID, agentNo, actionID);
	}

	Simulator Simulator::next(ActionID actionID)const
	{
		Simulator ret(teamID, agentNo, currentStage);
		ret.commandList.push(actionID);
		return ret;
	}
}