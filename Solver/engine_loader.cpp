#include "engine_loader.hpp"


namespace solver
{
	EngineLoader::EngineLoader(const std::wstring &engineName)
	{
		const std::wstring dllPath = L"engine/" + engineName + L".dll";
		moduleHandle = LoadLibrary(engineName.c_str());
		if(moduleHandle == NULL)
		{
			throw L"EngineManager : DLL�̓ǂݍ��݂Ɏ��s���܂���";
		}
		creator = reinterpret_cast<creator_t>(GetProcAddress(moduleHandle, "createEngine"));
		if(creator == NULL)
		{
			throw L"EngineManager : �C���X�^���X�����֐��̎擾�Ɏ��s���܂���";
		}
		destroyer = reinterpret_cast<destroyer_t>(GetProcAddress(moduleHandle, "destroyEngine"));
		if(destroyer == NULL)
		{
			throw L"EngineManager : �C���X�^���X�j���֐��̎擾�Ɏ��s���܂���";
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