#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t thread_num) : stop_(false) {
    for (size_t i = 0; i < thread_num; ++i) {
        workers_.emplace_back([this]() {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    cv_.wait(lock, [this]() {
                        return stop_ || !tasks_.empty();
                    });

                    if (stop_ && tasks_.empty())
                        return;

                    task = std::move(tasks_.front());
                    tasks_.pop();
                }

                task();
            }
        });
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (stop_) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        tasks_.push(std::move(task));
    }
    cv_.notify_one();
}

template<class F, class... Args>
auto ThreadPool::submit(F&& f, Args&&... args)
    -> std::future<std::invoke_result_t<F, Args...>>
{
    using RetType = std::invoke_result_t<F, Args...>;

    // 1️⃣ 把函数 + 参数打包成 packaged_task
    auto task = std::make_shared<std::packaged_task<RetType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    // 2️⃣ 拿到 future
    std::future<RetType> res = task->get_future();

    // 3️⃣ 转成 void() 丢进任务队列
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (stop_) {
            throw std::runtime_error("submit on stopped ThreadPool");
        }

        tasks_.emplace([task]() {
            (*task)();
        });
    }

    cv_.notify_one();
    return res;
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }
    cv_.notify_all();

    for (auto& t : workers_) {
        if (t.joinable())
            t.join();
    }
}