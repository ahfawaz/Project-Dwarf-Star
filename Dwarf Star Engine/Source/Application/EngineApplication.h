#pragma once
#include "../Memory Manager/MemoryManager.h"
#include "../Utilities/Util.h"

namespace DWS_Engine
{

	class CEngineApplication
	{
		DWS_Util::CUtil* m_pUtil;
		CMemoryManager* m_pMemoryManager;

	public:
		CEngineApplication();
		~CEngineApplication();
		CEngineApplication(CEngineApplication &_cpy);
		CEngineApplication& operator=(CEngineApplication &_assign);

		bool Initialize();
		void Shutdown();
		void Update();
	};


}