#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>
#include <unistd.h>
std::mutex mutex_;
std::condition_variable con;
int flag = 1;
static void thread_func1() {
    while(true) {
        std::unique_lock<std::mutex> mute(mutex_);
        con.wait(mute, []{return flag == 1;});
        flag = 2;
        std::cout << "aaaa" << std::endl;
        con.notify_all();
        
    }
}
static void thread_func2() {
    while(true) {
        std::unique_lock<std::mutex> mute(mutex_);
        con.wait(mute, []{return flag == 2;});
        flag = 1;
        std::cout << "bbbbb" << std::endl;
        con.notify_all();
    }
}

int main() {
    std::vector<std::thread> work_thread_pool;
    work_thread_pool.push_back(std::thread(thread_func1));
    work_thread_pool.push_back(std::thread(thread_func2));
    for (auto& t : work_thread_pool) {
        t.join();
    }
    return 0;
}
