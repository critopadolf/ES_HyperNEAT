#include "global_id.h"
#include "vectorRandom2.cpp"
#include <future>

inline int worker(global_id* gid, semaphore* S, int tid)
{
	std::random_device rnd_device;
	std::mt19937 me { rnd_device() };
	int nd = gid->getNID(tid);
	int cd = gid->getCID(tid, tid);
	/*
	S->acquire();
	std::cout << tid << " " << nd << " " << cd << "\n";
	S->release();
	*/
	return 0;
}

inline void test_gid()
{
	semaphore S;
	S.release();
	global_id gid(2, 1);
	std::vector<std::future<int>> km;
	for (int y = 0; y < 20; y++)
	{
		km.push_back(std::async(worker, &gid, &S, y));
	}
	for (int y = 0; y < 20; y++)
	{
		km[y].wait();
	}
	std::cout << gid;
}