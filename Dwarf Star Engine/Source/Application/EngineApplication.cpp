#include "../Application/stdafx.h"
#include "EngineApplication.h"

namespace DWS_Engine
{

#define SYSTEM_CHECK_FLAG(_sys_flag_, _check_) _sys_flag_ = ((short)_sys_flag_ | (short)_check_) << 1
#define SYSTEM_FLAGS 0b110 //Add a '1' b/w 'b' and '1' in the string(?) for every system of the engine.

	CEngineApplication::CEngineApplication()
	{
	}


	CEngineApplication::~CEngineApplication()
	{
		Shutdown();
	}

	CEngineApplication::CEngineApplication(CEngineApplication & _cpy)
	{
		*this = _cpy;
	}

	CEngineApplication & CEngineApplication::operator=(CEngineApplication & _assign)
	{
		if (this == &_assign)
			return *this;

		// TODO: insert return statement here
		return *this;
	}

	bool CEngineApplication::Initialize()
	{

		//Create Systems and initialize systems
		short system_flag = NULL;

		CMemoryManager *pMemory_Manager = new CMemoryManager;
		SYSTEM_CHECK_FLAG(system_flag, pMemory_Manager->Initialize());

		DWS_Util::CUtil *pUtil = new DWS_Util::CUtil;
		SYSTEM_CHECK_FLAG(system_flag, pUtil->Initialize());


		/*/////////////////////////////////////////////////////////////////
		//!Warning!!Warning!!Warning!!Warning!!Warning!!Warning!!Warning!//
		///////////////////////////////////////////////////////////////////
		//Don't forget to update SYSTEM_FLAGS if you added a new system!///
		///////////////////////////////////////////////////////////////////
		//!Warning!!Warning!!Warning!!Warning!!Warning!!Warning!!Warning!//
		/////////////////////////////////////////////////////////////////*/

		//Check to see if all systems were initialized properly. 
		//If true then run the program.
		if (!(system_flag & SYSTEM_FLAGS))
			return false;

		return true;
	}

	void CEngineApplication::Shutdown()
	{
		SHUTDOWN(m_pMemoryManager);
		SHUTDOWN(m_pUtil);
	}

	void CEngineApplication::Update()
	{
	}

}