#pragme once

#include <thread>
#include <mutex>
#include <vector>
#include <functional>

namespace DWS_Util {

	class CThreadManager
	{
		int m_nThreadsRunning;
		vector<thread> m_vThreadArray;
		vector<mutex> m_vMutexArray;
		vector<char> m_vLockValueArray;

	public:
		CThreadManager();
		CThreadManager(CThreadManager &_cpy);
		~CThreadManager();
		CThreadManager& operator=(CThreadManager &_assign);

		bool Initialize(int _prepare_threads_num);
		void Shutdown();

		thread& SafeCreateThread();
		mutex& SafeCreateMutex();
		char SafeCreateLock(char _lock_value);

		bool SafeJoinThread();
		bool SafeJoinAllThreads();
		void SafeThreadWait(char _lock_value);

		thread& SafeStartThread();

		mutex& SafeStartMutex();
	};

}