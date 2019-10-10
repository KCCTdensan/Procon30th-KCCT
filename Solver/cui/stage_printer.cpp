#include "stage_printer.hpp"
#include <iostream>


namespace solver::cui
{
	ColorID StagePrinter::backgroundColor(Position position)const noexcept
	{
		ColorID backgroundColorID;
		bool isAgentOnPanel = stage.isAgentOnPanel(position);
		switch(stage.getPanelTileStatus(position))
		{
		case TileID::red:
			backgroundColorID = isAgentOnPanel ? ColorID::red : ColorID::darkRed;
			break;

		case TileID::blue:
			backgroundColorID = isAgentOnPanel ? ColorID::blue : ColorID::darkBlue;
			break;

		default:
			backgroundColorID = ColorID::black;
			break;
		}
		return backgroundColorID;
	}

	ColorID StagePrinter::characterColor(Position position)const noexcept
	{
		unsigned colorMask = MASK_INTENSITY;
		if(stage.getPanelRegionStatus(position, TeamID::red))
		{
			colorMask |= MASK_RED;
		}
		if(stage.getPanelRegionStatus(position, TeamID::blue))
		{
			colorMask |= MASK_BLUE;
		}
		return static_cast<ColorID>(colorMask);
	}

	void StagePrinter::printPanel(Position position)const noexcept
	{
		changeColor(characterColor(position), backgroundColor(position));
		std::wprintf(L"%3d ", stage.getPanelPoint(position));
	}

	StagePrinter::StagePrinter(const StageInterface &stage)noexcept
		: stage(stage)
	{

	}

	void StagePrinter::print()const noexcept
	{
		for(uint8_t y = 0; y < stage.getFieldSize().height; ++y)
		{
			for(uint8_t x = 0; x < stage.getFieldSize().width; ++x)
			{
				printPanel(Position(static_cast<int8_t>(x), static_cast<int8_t>(y)));
			}
			changeColor(ColorID::white, ColorID::black);
			std::wcout << std::endl;
		}
		std::wcout << L"ターン : " << stage.getCurrentTurnNo() + 1 << std::endl;
		std::wcout << L"赤チーム(タイル) : " << stage.getScore().teamScores[static_cast<size_t>(TeamID::red)].tileScore << std::endl;
		std::wcout << L"赤チーム(領域) : " << stage.getScore().teamScores[static_cast<size_t>(TeamID::red)].regionScore << std::endl;
		std::wcout << L"青チーム(タイル) : " << stage.getScore().teamScores[static_cast<size_t>(TeamID::blue)].tileScore << std::endl;
		std::wcout << L"青チーム(領域) : " << stage.getScore().teamScores[static_cast<size_t>(TeamID::blue)].regionScore << std::endl;
		std::wcout << std::endl;
	}
}