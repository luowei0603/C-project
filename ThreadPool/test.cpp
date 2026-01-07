#include "ThreadPool.h"

int main() {
    ThreadPool pool(4);

    for (int i = 0; i < 10; ++i) {
        pool.enqueue([i]() {
            std::cout << "task " << i
                      << " run in thread "
                      << std::this_thread::get_id()
                      << std::endl;
        });
    }
}

int main_1() {
    ThreadPool pool(4);

    auto f1 = pool.submit([](int a, int b) {
        return a + b;
    }, 1, 2);

    auto f2 = pool.submit([] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return std::string("hello");
    });

    std::cout << f1.get() << std::endl;  // 3
    std::cout << f2.get() << std::endl;  // hello
}


