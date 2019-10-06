#include "engine_loader.hpp"


namespace solver
{
	EngineLoader::EngineLoader(const std::wstring &engineName)
	{
		const std::wstring dllPath = L"engine/" + engineName + L".dll";
		moduleHandle = LoadLibrary(engineName.c_str());
		if(moduleHandle == NULL)
		{
			throw L"EngineManager : DLLの読み込みに失敗しました";
		}
		creator = reinterpret_cast<creator_t>(GetProcAddress(moduleHandle, "createEngine"));
		if(creator == NULL)
		{
			throw L"EngineManager : インスタンス生成関数の取得に失敗しました";
		}
		destroyer = reinterpret_cast<destroyer_t>(GetProcAddress(moduleHandle, "destroyEngine"));
		if(destroyer == NULL)
		{
			throw L"EngineManager : インスタンス破棄関数の取得に失敗しました";
		}
	}

	EngineLoader::~EngineLoader()
	{
		FreeLibrary(moduleHandle);
	}

	engine::Interface *EngineLoader::createEngine()
	{
		return creator();
	}

	void EngineLoader::destroyEngine(engine::Interface *engine)
	{
		destroyer(engine);
	}
}