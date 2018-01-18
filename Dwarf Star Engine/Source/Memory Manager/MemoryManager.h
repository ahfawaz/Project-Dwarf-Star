#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace DWS_Engine
{
	struct tMemoryBlock
	{
		tMemoryBlock* pNext;
		tMemoryBlock* pPrev;
		unsigned int unBlockSize;
		signed int nAvailableSpace;
		char* pData;

		tMemoryBlock() : pNext(nullptr), pPrev(nullptr), unBlockSize(NULL), nAvailableSpace(NULL), pData(nullptr) {}
		~tMemoryBlock() { if (pData != nullptr) free(pData); }
		tMemoryBlock(const tMemoryBlock &_cpy) { *this = _cpy; }
		tMemoryBlock& operator=(const tMemoryBlock &_assign)
		{
			if (this == &_assign)
				return *this;


			this->pNext = _assign.pNext;
			this->pPrev = _assign.pPrev;
			this->unBlockSize = _assign.unBlockSize;
			this->nAvailableSpace = _assign.nAvailableSpace;
			delete pData;
			this->pData = _assign.pData;

			return *this;
		}

	};

	struct tDataChunk
	{
		tDataChunk *pNextChunk, *pPrevChunk;
		unsigned int unChunkSize;

		tDataChunk() : pNextChunk(nullptr), pPrevChunk(nullptr), unChunkSize(NULL) {}
		~tDataChunk() {}
		tDataChunk(const tDataChunk &_cpy) { *this = _cpy; }
		tDataChunk& operator=(const tDataChunk &_assign)
		{
			if (this == &_assign)
				return *this;

			this->pNextChunk = _assign.pNextChunk;
			this->pPrevChunk = _assign.pPrevChunk;
			this->unChunkSize = _assign.unChunkSize;

			return *this;
		}
	};

	struct tFragment
	{
		char *pFragmentAddress;
		tDataChunk pFragmentedChunk;
		unsigned int unFragmentSize;

		tFragment() : pFragmentAddress(nullptr), pFragmentedChunk(), unFragmentSize(NULL) {}
		~tFragment() {}
		tFragment(const tFragment &_cpy) { *this = _cpy; }
		tFragment& operator=(const tFragment &_assign)
		{
			if (this == &_assign)
				return *this;

			this->pFragmentAddress = _assign.pFragmentAddress;
			this->pFragmentedChunk = _assign.pFragmentedChunk;
			this->unFragmentSize = _assign.unFragmentSize;

			return *this;
		}
	};

	class CMemoryManager
	{
		//Private Members
		tMemoryBlock *m_pFirstBlock, *m_pLastBlock;
		tFragment m_pTailEnd;
		vector<tFragment> m_vFragmentList;
		unsigned int m_unTotalMemorySize;

	public:
		CMemoryManager();
		~CMemoryManager();

	private:
		CMemoryManager(CMemoryManager &_cpy);
		CMemoryManager& operator=(CMemoryManager &_assign);

	public:
		bool Initialize();
		void Shutdown();

		bool LoadData(void** _data, int _data_size);
		bool TrimData(char* _address, unsigned int _data_size);
		bool OnSystemReload();

	private:
		bool CreateMemoryBlock(unsigned int _memory_size = NULL);
		bool BreakMemoryBlock(tMemoryBlock* _address = nullptr);

	};
}