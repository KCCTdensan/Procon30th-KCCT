#include "simulator.hpp"
#include "../../random.hpp"


namespace solver::engine::ka31neo
{
	unsigned Simulator::pow2(unsigned x)
	{
		unsigned ret = 1;
		for(unsigned i = 0; i < x; ++i)
		{
			ret *= 2;
		}
		return ret;
	}

	CommandID Simulator::decideAgentCommand(const StageInterface &stage, TeamID team, uint8_t agentNo)const
	{		
		std::array<unsigned, numCommandID> actionEvaluationValues;
		const Position agentPosition = stage.getAgentPosition(team, agentNo);
		for(int i = 0; i < numCommandID; ++i)
		{
			const Command command = static_cast<CommandID>(i);
			if(!stage.canAgentAct(team, agentNo, command))
			{
				actionEvaluationValues[i] = 0;
				continue;
			}
			const Direction commandDirection = command.direction;
			const ActionID commandAction = command.action;
			const Position nextPosition = movedPosition(agentPosition, commandDirection);
			const int8_t panelPoint = stage.getPanelPoint(nextPosition);
			const TileID panelTileStatus = stage.getPanelTileStatus(nextPosition);
			if(panelTileStatus == toTile(team))
			{
				actionEvaluationValues[i] = commandAction == ActionID::removePanel ? pow2(-panelPoint / 4 + 4) : 0;
			}
			else
			{
				actionEvaluationValues[i] = pow2(panelPoint / 4 + 4);
			}
		}
		actionEvaluationValues[static_cast<size_t>(CommandID::stay)] /= 2;
		return static_cast<CommandID>(probability(actionEvaluationValues));
	}

	StageCommand Simulator::decideCommand(const StageInterface &stage)const
	{
		StageCommand command(stage.getNumAgents());
		for(int t = 0; t < numTeams; ++t)
		{
			for(uint8_t i = 0; i < stage.getNumAgents(); ++i)
			{
				command.teamCommands[t].commands[i] = decideAgentCommand(stage, static_cast<TeamID>(t), i);
			}
		}
		return command;
	}

	float Simulator::calculateReward(const Score &score)const
	{
		std::array<int16_t, numTeams> totalScores;
		for(int t = 0; t < numTeams; ++t)
		{
			totalScores[t] = score.teamScores[t].getTotalScore();
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
		std::queue<CommandID> commandList = this->commandList;
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

	bool Simulator::canAct(CommandID commandID)const noexcept
	{
		return currentStage.canAgentAct(teamID, agentNo, commandID);
	}

	Simulator Simulator::next(CommandID commandID)const
	{
		Simulator ret(teamID, agentNo, currentStage);
		ret.commandList.push(commandID);
		return ret;
	}
}