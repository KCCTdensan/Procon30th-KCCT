#pragma once

#include "../stage_interface.hpp"
#include "string_color.hpp"


namespace solver::cui
{
	class StagePrinter
	{
		const StageInterface &stage;

		ColorID backgroundColor(Position position)const noexcept;
		ColorID characterColor(Position position)const noexcept;
		void printPanel(Position position)const noexcept;

	public:
		StagePrinter(const StageInterface &stage)noexcept;
		void print()const noexcept;
	};
}