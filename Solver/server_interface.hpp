#pragma once

#include "com/com_interface.hpp"
#include "command.hpp"
#include "simulator/stage.hpp"


namespace solver
{
	class ServerInterface
	{
		const int numAgents;
		com::ComInterface comInterface;
		std::vector<int> agentIDs;

		com::SendActionDataOne convertCommand(Command command);

	public:
		ServerInterface();
		simulator::Stage getStage();
		void sendCommand(const TeamCommand &command);
		StageCommand recieveCommand();
	};
}