#pragma once

#include "command.hpp"
#include "team_id.hpp"
#include "position.hpp"
#include "tile_id.hpp"
#include "score.hpp"


namespace solver
{
	class StageInterface
	{
	public:
		virtual void act(const StageCommand &command) = 0;
		virtual Size getFieldSize()const = 0;
		virtual uint8_t getNumAgents()const = 0;
		virtual uint8_t getNumTurns()const = 0;
		virtual uint8_t getCurrentTurnNo()const = 0;
		virtual uint8_t getNumRemainingTurns()const = 0;
		virtual Position getAgentPosition(TeamID team, uint8_t agentNo)const = 0;
		virtual bool canAgentAct(TeamID team_id, uint8_t agentNo, ActionID action_id)const = 0;
		virtual int8_t getPanelPoint(Position position)const = 0;
		virtual TileID getPanelTileStatus(Position position)const = 0;
		virtual bool getPanelRegionStatus(Position position, TeamID team)const = 0;
		virtual bool isAgentOnPanel(Position position)const = 0;
		virtual Score getScore()const noexcept = 0;
		virtual StageInterface *copy()const = 0;
		virtual void destroy() = 0;
	};
}