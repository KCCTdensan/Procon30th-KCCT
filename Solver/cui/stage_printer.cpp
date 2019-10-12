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
		if(colorMask == MASK_INTENSITY)
		{
			return ColorID::white;
		}
		return static_cast<ColorID>(colorMask);
	}

	void StagePrinter::printPanel(Position position)const noexcept
	{
		changeColor(characterColor(position), backgroundColor(position));
		std::printf("%3d ", stage.getPanelPoint(position));
	}

	void StagePrinter::printField() const noexcept
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
	}

	void StagePrinter::printScore() const noexcept
	{
		std::cout << "ターン : " << static_cast<int>(stage.getCurrentTurnNo()) << std::endl;
		TeamScore redScore = stage.getScore().teamScores[static_cast<size_t>(TeamID::red)];
		TeamScore blueScore = stage.getScore().teamScores[static_cast<size_t>(TeamID::blue)];

		std::cout << "赤チーム : ";
		printf("%4d", redScore.getTotalScore());
		std::cout << " (タイル : ";
		printf("%4d", redScore.tileScore);
		std::cout << ", 領域 : ";
		printf("%4d", redScore.regionScore);
		std::cout << ")" << std::endl;

		std::cout << "青チーム : ";
		printf("%4d", blueScore.getTotalScore());
		std::cout << " (タイル : ";
		printf("%4d", blueScore.tileScore);
		std::cout << ", 領域 : ";
		printf("%4d", blueScore.regionScore);
		std::cout << ")" << std::endl;
	}

	StagePrinter::StagePrinter(const StageInterface &stage)noexcept
		: stage(stage)
	{

	}

	void StagePrinter::print()const noexcept
	{
		printField();
		printScore();
		std::cout << std::endl << std::endl;
	}
}