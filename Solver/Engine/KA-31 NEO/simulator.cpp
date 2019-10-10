#include "simulator.hpp"
#include "../../random.hpp"


namespace solver::engine::ka31neo
{
	StageCommand Simulator::getRandomCommand(uint8_t numAgents)const
	{
		StageCommand command;
		for(TeamID team : TeamID())
		{
			for(uint8_t i = 0; i < numAgents; ++i)
			{
				command.teamCommands[static_cast<size_t>(team)].commands[i] = static_cast<ActionID>(getRandomValue(1, numActionID - 1));
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
			switch(team_id)
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
			switch(team_id)
			{
			case TeamID::red:
				return redEvaluationValue;

			case TeamID::blue:
				return -redEvaluationValue;
			}
		}
		return 0.0f;
	}

	Simulator::Simulator(TeamID team_id, int8_t agentNo, const StageInterface &currentStage)
		: team_id(team_id), agentNo(agentNo), currentStage(currentStage)
	{

	}

	float Simulator::rollout()const
	{
		StageInterface *stage = currentStage.copy();
		std::queue<ActionID> commandList = this->commandList;
		for(int i = 0; i < commandList.size(); ++i)
		{
			StageCommand command = getRandomCommand(stage->getNumAgents());
			command.teamCommands[static_cast<size_t>(team_id)].commands[agentNo] = commandList.front();
			commandList.pop();
			stage->act(command);
		}
		for(uint8_t i = currentStage.getCurrentTurnNo() + static_cast<uint8_t>(commandList.size()); i < currentStage.getNumTurns(); ++i)
		{
			StageCommand command = getRandomCommand(stage->getNumAgents());
			stage->act(command);
		}
		Score finalScore = stage->getScore();
		stage->destroy();
		return calculateReward(finalScore);
	}

	bool Simulator::canAct(ActionID action_id)const noexcept
	{
		return currentStage.canAgentAct(team_id, agentNo, action_id);
	}

	Simulator Simulator::next(ActionID action_id)const
	{
		Simulator ret(team_id, agentNo, currentStage);
		ret.commandList.push(action_id);
		return ret;
	}
}