#include "../Application/stdafx.h"
#include "ErrorMessage.h"
#include "Util.h"

namespace DWS_Util
{

	CErrorMessage::CErrorMessage()
	{
	}


	CErrorMessage::~CErrorMessage()
	{
	}

	void CErrorMessage::PostError(eErrors _error_code)
	{
		switch (_error_code)
		{
		case BAD_INIT:
			break;
		default:
			break;
		}
	}

	string CErrorMessage::GetErrorMessage(eErrors _error_code)
	{
		string error_message = "ERROR: ";

		switch (_error_code)
		{
		case BAD_INIT:
			error_message += BAD_INIT + "; Engine failed to initialize properly.";
			break;
		default:
			error_message = "NO ERROR";
			break;
		}

		return error_message;
	}

}