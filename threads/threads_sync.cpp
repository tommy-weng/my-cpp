// refer to: https://blog.csdn.net/qq_48930954/article/details/124720677

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

bool ready = false;
std::mutex mtx;
std::condition_variable cv;

void print_thrd(int id)
{
	std::unique_lock<std::mutex> lck(mtx);
	//while (!ready){cv.wait(lck);}
    
	cv.wait(lck, [] {return ready; });
	std::cout << "thread:" << id << std::endl;
}

int main()
{
	std::thread threads[5];
	for (int i = 0; i < 5; i++)
	{
		threads[i] = std::thread(print_thrd, i);
	}

	std::cout << "start to notify threads:\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	{
		std::unique_lock<std::mutex> lck(mtx);
        
        ready = true;
        
		cv.notify_all();
		//cv.notify_one();
	}

	for (auto& th : threads)
	{
		th.join();
	}

	std::cout << "-------" << std::endl;
}
