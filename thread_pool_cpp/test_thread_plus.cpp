#include <iostream>
#include "thread_pool_plus.h"
#include <unistd.h>

int main() {
    ThreadPool tp(10);
    tp.Init();
    sleep(5);
    for (int i = 0; i < 1000; i++) {
        tp.add_task(Task({"1", "2", "3"}, [](std::vector<std::string> param){
            std::cout << param.size() << std::endl;
            for (int i = 0; i < param.size(); i++) {
                std::cout << param[i] << " ";
            }
            std::cout << std::endl;
        })); 
    }
    return 0;
}