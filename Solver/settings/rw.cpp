#include "rw.hpp"
#include "data_info.hpp"
#include <fstream>
#include <iostream>


namespace solver::settings
{
	Data read()
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

	void write(const Data &data)
	{
		std::ofstream file;
		file.open(fileName, std::ios::binary);
		if(!file)
		{
			std::wcout << L"データの書き込みに失敗しました" << std::endl;
		}
		file.write(reinterpret_cast<const char *>(&data), sizeof(Data));
		file.close();
	}
}