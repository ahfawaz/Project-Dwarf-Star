#pragma once

#include <queue>

#include "../Application/stdafx.h"

namespace MessengerSys 
{
	enum MessageID {eDEFAULT,};

	class CMessageBase
	{
		MessageID en_IDValue;

	public:
		CMessageBase() : en_IDValue(eDefault) {}
		CMessageBase(CMessageBase &_cpy) { *this = _cpy; }
		CMessageBase& operator=(CMessageBase &_assign)
		{
			if (this != &_assign)
			{
				this->en_IDValue = _assign.en_IDValue;
			}
			retrun *this;
		}
		virtual ~MessageParent() = 0;

		void SetMessageID(MessageID _id_value) { en_IDValue = _id_value; }
		MessageID GetMessageID() { return en_IDValue; }
	};

	class CMessengerSystem
	{
		queue<CMessageBase*> m_vMessages;
		int m_nMessagesThisTick;
		int m_nMessageLimitValue;

	public:
		CMessengerSystem();
		CMessengerSystem(CMessengerSystem &_cpy);
		CMessengerSystem& operator=(CMessengerSystem &_assign);

		bool Initialize();
		void Shutdown();
		void Update();
		
		bool UrgentMessage(CMessageBase* _the_message);
		void ClearQueue();
		
	private:
		void RunMessage(CMessageBase* _the_message);
	};
}
