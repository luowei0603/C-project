#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

class TokenBucketRateLimiter {
public:
    // capacity: 桶容量
    // refillRate: 每秒生成多少个 token
    TokenBucketRateLimiter(double capacity, double refillRate)
        : capacity_(capacity),
          tokens_(capacity),
          refillRate_(refillRate),
          lastRefillTime_(std::chrono::steady_clock::now()) {}

    bool tryAcquire(double permits = 1.0) {
        std::lock_guard<std::mutex> lock(mutex_);

        refill();

        if (tokens_ >= permits) {
            tokens_ -= permits;
            return true;
        }

        return false;
    }

private:
    void refill() {
        auto now = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed = now - lastRefillTime_;
        double seconds = elapsed.count();

        double newTokens = seconds * refillRate_;

        if (newTokens > 0) {
            tokens_ = std::min(capacity_, tokens_ + newTokens);
            lastRefillTime_ = now;
        }
    }

private:
    double capacity_;
    double tokens_;
    double refillRate_;

    std::chrono::steady_clock::time_point lastRefillTime_;
    std::mutex mutex_;
};

int main() {
    // 桶容量 10，每秒补充 5 个 token
    TokenBucketRateLimiter limiter(10, 5);

    for (int i = 0; i < 30; i++) {
        if (limiter.tryAcquire()) {
            std::cout << "request " << i << " allowed" << std::endl;
        } else {
            std::cout << "request " << i << " rejected" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}