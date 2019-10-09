#pragma once

#include "panel.hpp"
#include "../size.hpp"
#include "../position.hpp"
#include "../field_info.hpp"
#include "stage_flag.hpp"
#include <vector>


namespace solver::simulator
{
	class Field
	{
		const Size size;
		std::vector<Panel> panels;

	public:
		Field(const FieldInfo &fieldInfo)
			: size(fieldInfo.getSize())
		{
			for(uint8_t y = 0; y < size.height; ++y)
			{
				for(uint8_t x = 0; x < size.width; ++x)
				{
					Position position;
					position.x = x;
					position.y = y;
					panels.emplace_back(fieldInfo[position]);
				}
			}
		}
		const Panel &operator[](Position position)const
		{
			size_t index = static_cast<size_t>(size.width) *position.y + position.x;
			return panels[index];
		}
		const Size getSize()const noexcept
		{
			return size;
		}
		auto begin()noexcept
		{
			return panels.begin();
		}
		auto begin()const noexcept
		{
			return panels.begin();
		}
		auto end()noexcept
		{
			return panels.end();
		}
		auto end()const noexcept
		{
			return panels.end();
		}
		StageFlag decideStayingAgents(const StageCommand &command, uint8_t numAgents)
		{
			StageFlag ret(size, numAgents);
			for(TeamID team : TeamID())
			{
				for(uint8_t i = 0; i < numAgents; ++i)
				{
					ActionID agentCommand = command.teamCommands[static_cast<size_t>(team)].commands[i];
					Position nextPosition = movedPosition(this->agent(team, i).getPosition(), agentCommand);
					//エージェントが敵チームのタイルを剥がそうとする場合
					if(agentCommand != ActionID::stay)
					{
						//パネルの上のエージェントを確定させる
						Position agentPosition = this->agent(team, i).getPosition();
						ret.fieldFlag[agentPosition] = true;
						ret.agentFlag(team, i) = true;
					}
				}
			}
			return ret;
		}
	};
}