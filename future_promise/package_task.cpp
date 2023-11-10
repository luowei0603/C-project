// g++ -o test package_task.cpp -std=c++11 -lpthread
#include <thread>
#include <iostream>
#include <future>
#include <chrono>

using std::cout;
using std::endl;

int mythread(int val) {
    cout << "val = " << val << endl;
    cout << "mythrad() start" << "threadid = " << std::this_thread::get_id() << endl;

    std::chrono::milliseconds dura(5000); // sleep 5s
    std::this_thread::sleep_for(dura);

    cout << "mythread() end" << endl;
    return 5;
}

int main() {
    cout << "main threadid = " << std::this_thread::get_id() << endl;
    std::packaged_task<int(int)> myth(mythread);
    std::thread t1(std::ref(myth), 1);
    t1.join();
    std::future<int> fu = myth.get_future();

    cout << fu.get() << endl;
    cout << "main主函数执行结束" << endl;
    return 0;

}