#include "shared_ptr.h"

template <typename T>
class WeakPtr {
public:
    WeakPtr() noexcept : ptr_(nullptr), cb_(nullptr) {}

    // 从 shared_ptr 构造
    WeakPtr(const SharedPtr<T>& sp) noexcept
        : ptr_(sp.ptr_), cb_(sp.cb_) {
        if (cb_) {
            cb_->weak_count.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 拷贝构造
    WeakPtr(const WeakPtr& other) noexcept
        : ptr_(other.ptr_), cb_(other.cb_) {
        if (cb_) {
            cb_->weak_count.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 赋值
    WeakPtr& operator=(const WeakPtr& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            cb_  = other.cb_;
            if (cb_) {
                cb_->weak_count.fetch_add(1, std::memory_order_relaxed);
            }
        }
        return *this;
    }

    // 析构
    ~WeakPtr() {
        release();
    }

    // 是否过期
    bool expired() const noexcept {
        return !cb_ || cb_->shared_count.load(std::memory_order_acquire) == 0;
    }

    // ⭐ 核心：lock()
    SharedPtr<T> lock() const noexcept {
        if (!cb_) return SharedPtr<T>();

        long count = cb_->shared_count.load(std::memory_order_acquire);
        while (count > 0) {
            if (cb_->shared_count.compare_exchange_weak(
                    count, count + 1,
                    std::memory_order_acq_rel,
                    std::memory_order_acquire)) {
                // 成功“抢到”一个 shared_count
                return SharedPtr<T>(ptr_, cb_);
            }
            // 失败时 count 会被更新，继续判断
        }

        return SharedPtr<T>();  // 对象已销毁
    }

private:
    void release() noexcept {
        if (!cb_) return;

        if (cb_->weak_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            if (cb_->shared_count.load(std::memory_order_acquire) == 0) {
                delete cb_;
            }
        }

        ptr_ = nullptr;
        cb_  = nullptr;
    }

private:
    T* ptr_;
    ControlBlock* cb_;
};