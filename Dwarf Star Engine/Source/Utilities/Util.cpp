#include "../Application/stdafx.h"
#include "Util.h"

namespace DWS_Util
{
	CUtil::CUtil()
	{
	}

	CUtil::~CUtil()
	{
		Shutdown();
	}

	CUtil::CUtil(CUtil & _cpy)
	{
		*this = _cpy;
	}

	CUtil & CUtil::operator=(CUtil & _assign)
	{
		if (this == &_assign)
			return *this;
		// TODO: insert return statement here

		return *this;
	}

	bool CUtil::Initialize()
	{
		return true;
	}

	void CUtil::Shutdown()
	{
	}

}