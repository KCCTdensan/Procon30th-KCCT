#pragma once


namespace solver
{
	struct Size
	{
		uint8_t width;
		uint8_t height;

		Size()
			: width(0), height(0)
		{

		}
		Size(uint8_t width, uint8_t height)
			: width(width), height(height)
		{

		}
	};
}