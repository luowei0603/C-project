#include <atomic>

struct ControlBlock {
    std::atomic<long> shared_count;
    std::atomic<long> weak_count;

    ControlBlock()
        : shared_count(1), weak_count(0) {}
};

template <typename T>
class WeakPtr;  // 前向声明

template <typename T>
class SharedPtr {
public:
    SharedPtr() noexcept : ptr_(nullptr), cb_(nullptr) {}

    explicit SharedPtr(T* ptr) : ptr_(ptr) {
        if (ptr_) {
            cb_ = new ControlBlock();
        } else {
            cb_ = nullptr;
        }
    }

    // 拷贝构造
    SharedPtr(const SharedPtr& other) noexcept
        : ptr_(other.ptr_), cb_(other.cb_) {
        if (cb_) {
            cb_->shared_count.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 从 weak_ptr lock 构造
    SharedPtr(T* ptr, ControlBlock* cb) noexcept
        : ptr_(ptr), cb_(cb) {}

    // 赋值
    SharedPtr& operator=(const SharedPtr& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            cb_  = other.cb_;
            if (cb_) {
                cb_->shared_count.fetch_add(1, std::memory_order_relaxed);
            }
        }
        return *this;
    }

    ~SharedPtr() {
        release();
    }

    T* get() const noexcept { return ptr_; }
    long use_count() const noexcept {
        return cb_ ? cb_->shared_count.load(std::memory_order_acquire) : 0;
    }

    explicit operator bool() const noexcept {
        return ptr_ != nullptr;
    }

private:
    friend class WeakPtr<T>;

    void release() noexcept {
        if (!cb_) return;

        if (cb_->shared_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            delete ptr_;
            ptr_ = nullptr;

            if (cb_->weak_count.load(std::memory_order_acquire) == 0) {
                delete cb_;
                cb_ = nullptr;
                return;
            }
        }

        ptr_ = nullptr;
        cb_  = nullptr;
    }

private:
    T* ptr_;
    ControlBlock* cb_;
};