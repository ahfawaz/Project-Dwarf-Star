#pragma once
#include <string>

namespace DWS_Util
{
	class CErrorMessage
	{
	public:
		CErrorMessage();
		~CErrorMessage();

		void PostError(eErrors _error_code);

	private:
		string GetErrorMessage(eErrors _error_code);
	};

}
