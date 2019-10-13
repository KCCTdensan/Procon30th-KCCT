#include "server_interface.hpp"


namespace solver
{
	com::SendActionDataOne ServerInterface::convertCommand(Command command)
	{
		com::SendActionDataOne ret;
		Direction direction = command.direction;
		ret.aentID;
		ret.dx = direction.getDx();
		ret.dy = direction.getDy();
		ret.type = command.action == ActionID::setTileOnPanel ? "move" : "remove";
		return ret;
	}

	ServerInterface::ServerInterface()
		: comInterface("", "", "", "d55101d94c146f52bb03345bba0c58c01435cd0314a95518eeb4518f182c774a")
	{

	}

	simulator::Stage ServerInterface::getStage()
	{
		uint8_t numTurns;
		FieldInfo fieldInfo;
		AgentInfo agentInfo;
		simulator::Stage ret(numTurns, fieldInfo, agentInfo);
		agentIDs.resize(ret.getNumAgents());
		return ret;
	}

	void ServerInterface::sendCommand(const TeamCommand &command)
	{
		com::SendActionData data;
		data.actions.resize(command.commands.size());
		for(int i = 0; i < data.actions.size(); ++i)
		{
			data.actions[i] = convertCommand(command.commands[i]);
		}
		comInterface.sendActionData(data);
	}

	StageCommand ServerInterface::recieveCommand()
	{

	}
}