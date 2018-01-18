#include "../Application/stdafx.h"
#include "MemoryManager.h"

namespace DWS_Engine
{

#define CHUNK_HEADER_SIZE sizeof(tDataChunk)
#define	MAX_BLOCK_SIZE 10000000u

	CMemoryManager::CMemoryManager()
	{
		m_pFirstBlock = nullptr;
		m_pLastBlock = nullptr;
	}

	CMemoryManager::~CMemoryManager()
	{
		if (m_pFirstBlock != nullptr || m_pLastBlock != nullptr)
		{
			this->Shutdown();
		}
	}

	CMemoryManager::CMemoryManager(CMemoryManager &cpy)
	{
		*this = cpy;
	}

	CMemoryManager& CMemoryManager::operator=(CMemoryManager &assign)
	{
		return *this;
	}

	bool CMemoryManager::Initialize()
	{
		return this->CreateMemoryBlock();
	}

	void CMemoryManager::Shutdown()
	{
		tMemoryBlock* temp;
		while (m_pFirstBlock != nullptr && m_pLastBlock != nullptr)
		{
			temp = m_pFirstBlock;
			temp->pNext->pPrev = nullptr;
			temp->pNext = nullptr;
			free(m_pFirstBlock->pData);
			m_pFirstBlock = temp->pNext;
			delete temp;
			temp = nullptr;
		}

		m_pFirstBlock = nullptr;
		m_pLastBlock = nullptr;
		m_vFragmentList.empty();

	}

	bool CMemoryManager::LoadData(void ** _data, int _data_size)
	{
		//Make sure there is data to load.
		if (_data == nullptr || *_data == nullptr || _data_size == NULL)
			return false;

		tDataChunk new_chunk;
		void* address_manip = nullptr;

		//Check Fragment List
		tFragment temp_frag;
		for (size_t i = 0; i < m_vFragmentList.size(); i++)
		{
			temp_frag = m_vFragmentList[i];
			if (temp_frag.unFragmentSize >= _data_size + CHUNK_HEADER_SIZE)
			{
				new_chunk.pNextChunk = temp_frag.pFragmentedChunk.pNextChunk;
				new_chunk.pPrevChunk = temp_frag.pFragmentedChunk.pPrevChunk;
				new_chunk.unChunkSize = _data_size;
				new_chunk.pPrevChunk->pNextChunk = (tDataChunk*)temp_frag.pFragmentAddress;
				new_chunk.pNextChunk->pPrevChunk = (tDataChunk*)temp_frag.pFragmentAddress;

				memcpy_s(temp_frag.pFragmentAddress, temp_frag.unFragmentSize, &new_chunk, CHUNK_HEADER_SIZE);
				address_manip = (char*)temp_frag.pFragmentAddress + CHUNK_HEADER_SIZE;
				memcpy_s(address_manip, temp_frag.unFragmentSize, _data, _data_size);
				return true;
			}
		}

		//Making sure there is enough room in the memory block to copy the data.
		if (m_pTailEnd.unFragmentSize < _data_size + CHUNK_HEADER_SIZE)
		{
			m_vFragmentList.push_back(m_pTailEnd);
			if (!CreateMemoryBlock())
				return false;
		}

		//creating the data chunk header
		new_chunk.pNextChunk = m_pTailEnd.pFragmentedChunk.pNextChunk;
		new_chunk.pPrevChunk = m_pTailEnd.pFragmentedChunk.pPrevChunk;
		new_chunk.unChunkSize = _data_size;
		new_chunk.pPrevChunk->pNextChunk = (tDataChunk*)m_pTailEnd.pFragmentAddress;
		new_chunk.pNextChunk->pPrevChunk = (tDataChunk*)m_pTailEnd.pFragmentAddress;

		//Copy the header data and the actual data into the pool of memory.
		memcpy_s(m_pTailEnd.pFragmentAddress, m_pTailEnd.unFragmentSize, &new_chunk, CHUNK_HEADER_SIZE);
		address_manip = (char*)m_pTailEnd.pFragmentAddress + CHUNK_HEADER_SIZE;
		memcpy_s(address_manip, m_pTailEnd.unFragmentSize, _data, _data_size);

		//Since we added to end of the chain of memory (not including fragments) lets update m_pTailEnd.
		temp_frag = m_pTailEnd;
		m_pTailEnd.pFragmentAddress = (char*)address_manip + _data_size;
		m_pTailEnd.pFragmentedChunk.pNextChunk = nullptr;
		m_pTailEnd.pFragmentedChunk.pPrevChunk = (tDataChunk*)temp_frag.pFragmentAddress;
		m_pTailEnd.unFragmentSize = m_pLastBlock->nAvailableSpace = m_pLastBlock->nAvailableSpace - (_data_size + CHUNK_HEADER_SIZE);

		return true;
	}

	bool CMemoryManager::TrimData(char* _address, unsigned int _data_size)
	{
		if (_address == nullptr || _data_size == NULL)
			return false;

		tFragment new_fragment;
		tDataChunk *temp_chunk = (tDataChunk*)_address;
		new_fragment.pFragmentAddress = _address;
		new_fragment.pFragmentedChunk = *temp_chunk;
		new_fragment.unFragmentSize = _data_size + CHUNK_HEADER_SIZE;

		_address += CHUNK_HEADER_SIZE;
		memcpy_s(_address, _data_size, NULL, temp_chunk->unChunkSize);
		m_vFragmentList.push_back(new_fragment);

		return true;
	}

	bool CMemoryManager::OnSystemReload()
	{
		//To Do later
		return false;
	}

	bool CMemoryManager::CreateMemoryBlock(unsigned int _memory_size)
	{
		tMemoryBlock *new_block = new tMemoryBlock;
		new_block->nAvailableSpace = NULL;
		new_block->pData = nullptr;
		new_block->pNext = nullptr;
		new_block->pPrev = nullptr;
		new_block->unBlockSize = NULL;

		if (_memory_size == 0)
			new_block->pData = (char*)malloc(MAX_BLOCK_SIZE);
		else
			new_block->pData = (char*)malloc(_memory_size);

		if (new_block->pData == nullptr)
		{
			delete new_block;
			return false;
		}

		if (m_pFirstBlock == nullptr)
		{
			m_pFirstBlock = m_pLastBlock = new_block;
		}
		else
		{
			new_block->pPrev = m_pLastBlock;
			m_pLastBlock->pNext = new_block;

			m_pLastBlock = new_block;
		}

		return true;
	}

	bool CMemoryManager::BreakMemoryBlock(tMemoryBlock * _address)
	{

		if (_address)
		{
			if (_address->pNext)
				_address->pPrev->pPrev = _address->pNext;
			if (_address->pPrev)
				_address->pNext->pPrev = _address->pPrev;

			if (m_pFirstBlock == _address)
				m_pFirstBlock = _address->pNext;
			if (m_pLastBlock == _address)
				m_pLastBlock = _address->pPrev;

			free(_address->pData);

			delete _address;

			return true;
		}
		return false;
	}

}