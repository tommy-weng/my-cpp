#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

using std::cout;
using std::endl;

std::atomic<bool> ready{false};

std::atomic<int> sum{0};
// int sum{0};

std::mutex mtx{};

void read_thread(int id)
{
    cout << "Read thread # " << id << endl;
    // while(not ready){std::this_thread::yield();}
    while(not ready.load());
    for (int i{0}; i < 10000; i++)
    {
        // std::lock_guard<std::mutex> lkg{mtx};
        sum--;
        cout << "Read sum: " << sum << endl;
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void write_therad(int id)
{
    cout << "Write thread # " << id << endl;
    // while(not ready){std::this_thread::yield();}
    while(not ready.load());
    for (int i{0}; i < 10000; i++)
    {
        // std::unique_lock<std::mutex> lkg{mtx};
        sum++;
        cout << "Write sum:" << sum << endl;
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    std::thread th1(read_thread, 10);
    std::thread th2(write_therad, 11);

    ready = true;
    th1.join();
    th2.join();
    return 0;
}