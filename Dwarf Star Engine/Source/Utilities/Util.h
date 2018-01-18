#pragma once
#include "ErrorMessage.h"

namespace DWS_Util
{
	//Foward Include

	//Useful Defines
#define SHUTDOWN(x) if(x) x->Shutdown(); delete x; x = nullptr

	//Enums used by all utilities
	enum eErrors { BAD_INIT = 2001, };


	class CUtil
	{
		//add Utility Classes that will launch here when program starts.
		CErrorMessage util_ErrorMessage;

	public:

		CUtil();
		~CUtil();
		CUtil(CUtil &_cpy);
		CUtil& operator=(CUtil &_assign);

		bool Initialize();
		void Shutdown();
	};
}