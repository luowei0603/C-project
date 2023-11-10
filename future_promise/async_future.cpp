// g++ -o test async_future.cpp -std=c++11 -lpthread
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
    std::future<int> fu = std::async(mythread, 2);
    int result = fu.get();
    cout << "result = " << result << endl;
    cout << "main主函数执行结束" << endl;
    return 0;

}