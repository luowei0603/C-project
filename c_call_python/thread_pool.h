#ifndef THREAD_POOL_CPP_H
#define THREAD_POOL_CPP_H
#include <iostream>
#include <deque>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <boost/python.hpp> 
template <typename T>
class ThreadPool {
private:
    std::deque<std::pair<std::function<void(T)>, T>> task_que;
    std::vector<std::thread> work_thread_pool;
    int max_thread_num;
    std::mutex t_mutex;
    std::condition_variable t_cond;

public:
    ThreadPool(int thread_num): max_thread_num(thread_num) {

    }
    ~ThreadPool(){
        for (auto& t : work_thread_pool) {
            t.join();
        }
    };
    bool Init() {
        for (int i = 0; i < max_thread_num; i++) {
            work_thread_pool.push_back(std::thread(start_work, this));
        }
        return true;
    }
    static void start_work(void* arg) {
        ThreadPool* pool = static_cast<ThreadPool*>(arg);
        while (true) {
            std::unique_lock<std::mutex> lk(pool->t_mutex);
            pool->t_cond.wait(lk, [&]{return !pool->task_que.empty();});
            auto task = pool->task_que.front();
            auto f = task.first;
            T f_arg = task.second;
            pool->task_que.pop_front();
            std::cout << pthread_self() << " get task, task_que_size:" << pool->task_que.size() << std::endl;
            lk.unlock();
            f(f_arg);
        }
    }
    void add_task(std::function<void(T)> f, T arg) {
        std::unique_lock<std::mutex> lk(t_mutex);
        task_que.push_back(std::make_pair(std::move(f), arg));
        t_cond.notify_one();
    }

};
#endif