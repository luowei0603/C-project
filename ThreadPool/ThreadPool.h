#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>

class ThreadPool {
public:
    explicit ThreadPool(size_t thread_num);
    ~ThreadPool();

    // 无返回值版本
    void enqueue(std::function<void()> task);

    // ⭐ 有返回值版本（重点）
    template<class F, class... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<std::invoke_result_t<F, Args...>>;

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex mutex_;
    std::condition_variable cv_;
    bool stop_;
};

