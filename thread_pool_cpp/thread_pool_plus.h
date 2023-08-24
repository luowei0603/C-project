#ifndef THREAD_POOL_CPP_H
#define THREAD_POOL_CPP_H
#include <iostream>
#include <deque>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

class Task{
public:
    Task(std::vector<std::string>&& params, std::function<void(std::vector<std::string> extrator)>&& extrator):_params(params), _extrator(extrator) {}
    ~Task() {}
    std::vector<std::string> _params;
    std::function<void(std::vector<std::string>)> _extrator;
    void run() {
        _extrator(_params);
    }
};

class ThreadPool {
private:
    std::deque<Task> task_que;
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
            pool->task_que.pop_front();
            std::cout << pthread_self() << " get task, task_que_size:" << pool->task_que.size() << std::endl;
            lk.unlock();
            task.run();
        }
    }
    void add_task(Task task) {
        std::unique_lock<std::mutex> lk(t_mutex);
        task_que.push_back(std::move(task));
        t_cond.notify_one();
    }

};
#endif