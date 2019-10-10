#pragma once

#include "../stage_interface.hpp"
#include "field.hpp"
#include "agent_manager.hpp"
#include "score_manager.hpp"
#include "../command.hpp"


namespace solver::simulator
{
	class Stage : public StageInterface
	{
		const uint8_t numTurns;
		uint8_t currentTurnNo;
		Field field;
		AgentManager agentManager;
		ScoreManager scoreManager;

		bool willAgentStay(const Agent &agent, ActionID command)const;
		bool willAgentRemoveTile(const Agent &agent, ActionID command)const;
		StageFlag decideFirstAgentStayingPanels(StageCommand &command)const;
		StageFlag decideAgentOverlappingPanels(const StageFlag &isDecided, StageCommand &command)const;
		StageFlag decideNextStayingAgents(const StageFlag &isDecided, StageCommand &command)const;

	public:
		Stage(uint8_t numTurns, const FieldInfo &fieldInfo, const AgentInfo &agentManagerInfo);
		void act(const StageCommand &command)override;
		Size getFieldSize()const noexcept override;
		uint8_t getNumAgents()const noexcept override;
		uint8_t getNumTurns()const noexcept override;
		uint8_t getCurrentTurnNo()const noexcept override;
		uint8_t getNumRemainingTurns()const noexcept override;
		bool canAgentAct(TeamID team_id, uint8_t agentNo, ActionID action_id)const noexcept override;
		int8_t getPanelPoint(Position position)const noexcept override;
		TileID getPanelTileStatus(Position position)const noexcept override;
		bool getPanelRegionStatus(Position position, TeamID team)const noexcept override;
		bool isAgentOnPanel(Position position)const noexcept override;
		Score getScore()const noexcept override;
		StageInterface *copy()const override;
		void destroy()override;
	};
}