#include "writer.hpp"
#include "data_info.hpp"
#include <fstream>
#include <iostream>


namespace solver
{
	namespace config
	{
		void Writer::write(const Data &data)
		{
			std::ofstream file;
			file.open(fileName, std::ios::binary);
			if(!file)
			{
				std::wcout << L"ƒf[ƒ^‚Ì‘‚«ž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½" << std::endl;
			}
			file.write(reinterpret_cast<const char *>(&data), sizeof(Data));
			file.close();
		}
	}
}