#pragma once


namespace solver::cui
{
	constexpr unsigned MASK_INTENSITY = 0x08;
	constexpr unsigned MASK_RED = 0x04;
	constexpr unsigned MASK_GREEN = 0x02;
	constexpr unsigned MASK_BLUE = 0x01;

	enum class ColorID
	{
		black,
		darkBlue,
		darkGreen,
		darkCyan,
		darkRed,
		darkViolet,
		darkYellow,
		gray,
		lightGray,
		blue,
		green,
		cyan,
		red,
		violet,
		yellow,
		white
	};

	void changeColor(ColorID characterColor, ColorID backgroundColor);
}