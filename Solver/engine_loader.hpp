#pragma once

#include "engine/interface.hpp"
#include <string>
#include <Windows.h>


namespace solver
{
	class EngineLoader
	{
		using creator_t = engine::Interface * (*)();
		using destroyer_t = void(*)(engine::Interface *);

		HMODULE moduleHandle;
		creator_t creator;
		destroyer_t destroyer;
		
	public:
		EngineLoader(const std::wstring &engineName);
		~EngineLoader();
		engine::Interface *createEngine();
		void destroyEngine(engine::Interface *engine);
	};
}