#pragma once

#include "com/com_interface.hpp"
#include "command.hpp"
#include "simulator/stage.hpp"
#include "com/send_action_data.hpp"


namespace solver
{
	class ServerInterface
	{
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