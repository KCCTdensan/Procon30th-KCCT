#pragma once

#include "com/com_interface.hpp"
#include "command.hpp"
#include "simulator/stage.hpp"


namespace solver
{
	class ServerInterface
	{
		com::ComInterface comInterface;

	public:
		ServerInterface();
		simulator::Stage getStage();
		void sendCommand(const TeamCommand &command);
		StageCommand recieveCommand();
	};
}