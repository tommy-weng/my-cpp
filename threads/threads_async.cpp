// refer to: https://blog.csdn.net/qq_48930954/article/details/124720677

#include <iostream>
#include <future>
#include <thread>

int async_task(int count)
{
	int sum = 0;
	for (int i = 1; i <= count; i++)
	{
		sum += i;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return sum;
}

int main()
{
	std::cout << "start async\n";
	//int为返回类型
	std::future<int> fut = std::async(async_task, 10);
	std::cout << "wait for result for 15 seconds...\n";

	std::chrono::seconds span(15);
	if (fut.wait_for(span) == std::future_status::timeout)
	{
		std::cout << "async timeout\n";
	}
	else
	{
		std::cout << "result:" << fut.get() << std::endl;
	}

}