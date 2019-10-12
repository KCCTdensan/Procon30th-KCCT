#pragma once

#include "../stage_interface.hpp"
#include "field.hpp"
#include "agent_manager.hpp"
#include "score_manager.hpp"
#include "command_normalizer.hpp"
#include "../stage_command.hpp"


namespace solver::simulator
{
	class Stage : public StageInterface
	{
		const uint8_t numTurns;
		uint8_t currentTurnNo;
		Field field;
		AgentManager agentManager;
		ScoreManager scoreManager;
		CommandNormalizer commandNormalizer;

		bool willAgentStay(const Agent &agent, CommandID command)const;
		bool willAgentRemoveTile(const Agent &agent, CommandID command)const;
		StageFlag decideFirstAgentStayingPanels(StageCommand &command)const;
		void decideAgentOverlappingPanels(StageFlag &isDecided, StageCommand &command)const;
		void decideNextStayingAgents(StageFlag &isDecided, StageCommand &command)const;

	public:
		Stage(const Stage &stage);
		Stage(uint8_t numTurns, const FieldInfo &fieldInfo, const AgentInfo &agentManagerInfo);
		void act(const StageCommand &command)override;
		Size getFieldSize()const noexcept override;
		uint8_t getNumAgents()const noexcept override;
		uint8_t getNumTurns()const noexcept override;
		uint8_t getCurrentTurnNo()const noexcept override;
		uint8_t getNumRemainingTurns()const noexcept override;
		Position getAgentPosition(TeamID team, uint8_t agentNo)const;
		bool canAgentMovePositionally(TeamID team, uint8_t agentNo, Direction direction)const override;
		bool canAgentAct(TeamID team, uint8_t agentNo, Command command)const override;
		int8_t getPanelPoint(Position position)const noexcept override;
		TileID getPanelTileStatus(Position position)const noexcept override;
		bool getPanelRegionStatus(Position position, TeamID team)const override;
		bool isAgentOnPanel(Position position)const noexcept override;
		Score getScore()const noexcept override;
		StageInterface *copy()const override;
		void destroy()override;
	};
}