#include "CMessengerSystem.h"
#include "../Utilities/Util.h"
#include <mutex>
#include <thread>

#define LIST_INIT_SIZE 200

namespace MessengerSys
{
	CMessengerSystem::CMessengerSystem()
	{
		m_nMessageLimitValue = NULL;
		m_nMessagesThisTick = NULL;
	}

	CMessengerSystem::CMessengerSystem(CMessengerSystem &_cpy)
	{
		*this = _cpy;
	}

	CMessengerSystem& CMessengerSystem::operator=(CMessengerSystem &_assign)
	{
		if (this != &_assign)
		{
			this->ClearQueue();
			this->m_vMessages = _assign.m_vMessages;

			this->m_nMessageLimitValue = _assign.m_nMessageLimitValue;
			this->m_nMessagesThisTick = _assign.m_nMessagesThisTick;
		}
		return *this;
	}

	CMessengerSystem::~CMessengerSystem()
	{
		Shutdown();
	}

	bool CMessengerSystem::Initialize()
	{
		return true;
	}

	void CMessengerSystem::Shutdown()
	{
		ClearQueue();
	}

	void CMessengerSystem::Update()
	{
		//Lets use as many threads as we can, safely, to achieve fast results running through all messages.
		CMessageBase* current_message = nullptr;

		do
		{
			current_message = m_vMessages.front();
			m_vMessages.pop();

			if (current_message)
			{
				RunMessage(current_message);
			}

			DELETE(current_message);
			
		}while (NULL > m_nMessagesThisTick)

	}

	bool CMessengerSystem::UrgentMessage(CMessageBase* _the_message)
	{
		RunMessage(_the_message);
	}

	void CMessengerSystem::ClearQueue()
	{
		while (m_vMessages.size())
		{
			delete m_vMessages.front();
			m_vMessages.pop();
		}
	}

	void CMessengerSystem::RunMessage(CMessageBase* _the_message)
	{
		MessageID value = _the_message->GetMessageID();

		switch (value)
		{
		case MessengerSys::eDEFAULT:
			break;
		default:
			break;
		}
	}
}