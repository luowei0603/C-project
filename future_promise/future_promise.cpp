
// g++ -o test future_promise.cpp -std=c++11 -lpthread
#include <thread>
#include <iostream>
#include <future>
#include <chrono>

using std::cout;
using std::endl;

void mythread(std::promise<int>& tmpp, int calc) {
    cout << "mythrad() start" << "threadid = " << std::this_thread::get_id() << endl;
    
    // 模拟进行复杂运算
    calc++;
    calc *= 10;
    std::chrono::milliseconds dura(5000); // sleep 5s
    std::this_thread::sleep_for(dura);

    // finally，get result
    int result = calc;
    tmpp.set_value(result);  // 将结果保存在tmpp对象中
    cout << "mythread() end" << " threadid = " << std::this_thread::get_id() << endl;
}

void mythread2(std::future<int>& tmpf) {
    auto result = tmpf.get();
    cout << "mythread2 result = " << result << endl;
    return;
}
int main() {
    cout << "main threadid = " << std::this_thread::get_id() << endl;
    std::promise<int> myprom;  // 声明std::promise对象，保存的值为int类型

    // 创建t1线程，传入参数mythread及myporm
    std::thread t1(mythread, std::ref(myprom), 180);
    t1.join();

    // 获取结果值
    std::future<int> fu1 = myprom.get_future(); // promise喝future绑定用于获取线程返回值
  
    std::thread t2(mythread2, std::ref(fu1));
    t2.join();
    cout << "main主函数执行结束" << endl;
    return 0;

}
int main1() {
    cout << "main threadid = " << std::this_thread::get_id() << endl;
    std::promise<int> myprom;  // 声明std::promise对象，保存的值为int类型

    // 创建t1线程，传入参数mythread及myporm
    std::thread t1(mythread, std::ref(myprom), 180);
    // t1.join();

    // 获取结果值
    std::future<int> fu1 = myprom.get_future(); // promise喝future绑定用于获取线程返回值
    auto result = fu1.get();   // get只能执行一次，不能多次get

    t1.join();

    cout << "result = " << result << endl;
    cout << "main主函数执行结束" << endl;
    return 0;

}


