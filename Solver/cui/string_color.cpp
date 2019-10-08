#include "string_color.hpp"
#include <Windows.h>


namespace solver::cui
{
	void changeColor(ColorID characterColor, ColorID backgroundColor)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD attr = 0;
		if(static_cast<unsigned>(characterColor) & MASK_INTENSITY)
		{
			attr |= FOREGROUND_INTENSITY;
		}
		if(static_cast<unsigned>(characterColor) & MASK_RED)
		{
			attr |= FOREGROUND_RED;
		}
		if(static_cast<unsigned>(characterColor) & MASK_GREEN)
		{
			attr |= FOREGROUND_GREEN;
		}
		if(static_cast<unsigned>(characterColor) & MASK_BLUE)
		{
			attr |= FOREGROUND_BLUE;
		}
		if(static_cast<unsigned>(backgroundColor) & MASK_INTENSITY)
		{
			attr |= BACKGROUND_INTENSITY;
		}
		if(static_cast<unsigned>(backgroundColor) & MASK_RED)
		{
			attr |= BACKGROUND_RED;
		}
		if(static_cast<unsigned>(backgroundColor) & MASK_GREEN)
		{
			attr |= BACKGROUND_GREEN;
		}
		if(static_cast<unsigned>(backgroundColor) & MASK_BLUE)
		{
			attr |= BACKGROUND_BLUE;
		}
		SetConsoleTextAttribute(hConsole, attr);
	}
}