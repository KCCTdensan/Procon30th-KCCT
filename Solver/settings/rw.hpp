#pragma once

#include "data.hpp"


namespace solver::settings
{
	Data read();
	void write(const Data &data);
}