#pragma once

#include "data.hpp"


namespace solver
{
	namespace config
	{
		class Reader
		{
		public:
			Data read();
		};
	}
}