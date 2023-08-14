#include <iostream>
#include "thread_pool.h"
#include <unistd.h>

int main() {
    ThreadPool tp(10);
    tp.Init();
    sleep(5);
    for (int i = 0; i < 1000; i++) {
        tp.add_task([=]{std::cout << "this is id:" << i << std::endl;}); 
    }
    return 0;
}