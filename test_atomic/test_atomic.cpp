#include<iostream>
#include<atomic>
#include<thread>
#include<map>
using namespace std;
map<string, atomic<int> > my_map;
//map<string, int> my_map;


void Add()
{
    for(int i=0;i<10000000;i++) 
    {
        my_map["test"]++;
    }
}

int main()
{
    my_map["test"] = 0;
    clock_t startClock = clock();   // 记下开始时间
    // 3个线程,创建即运行
    thread t1(Add);
    thread t2(Add);
    thread t3(Add);
    // 等待3个线程结束
    t1.join();
    t2.join();
    t3.join();
    clock_t endClock = clock();     // 记下结束时间
    cout<<"耗时:"<<endClock-startClock<<",单位:"<<CLOCKS_PER_SEC<<",result:"<<my_map["test"]<<endl;
    return 0;
}
