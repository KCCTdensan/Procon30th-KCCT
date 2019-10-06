#include "reader.hpp"
#include "data_info.hpp"
#include <fstream>
#include <iostream>


namespace solver
{
	namespace config
	{
		Data Reader::read()
		{
			Data ret;
			std::ifstream file;
			file.open(fileName, std::ios::binary);
			if(!file)
			{
				std::wcout << L"データの読み込みに失敗しました" << std::endl;
			}
			file.read(reinterpret_cast<char *>(&ret), sizeof(Data));
			file.close();
			return ret;
		}
	}
}