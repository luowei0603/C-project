#include <atomic>
#include <cstddef>
#include <vector>
#include <cassert>

template<typename T>
class MPMCQueue {
public:
    explicit MPMCQueue(size_t capacity)
        : capacity_(capacity),
          buffer_(capacity),
          enqueue_pos_(0),
          dequeue_pos_(0) {
        assert((capacity_ & (capacity_ - 1)) == 0 &&
               "capacity must be power of two");

        for (size_t i = 0; i < capacity_; ++i) {
            buffer_[i].sequence.store(i, std::memory_order_relaxed);
        }
    }

    bool enqueue(const T& data);
    bool dequeue(T& data);

private:
    struct Cell {
        std::atomic<size_t> sequence;
        T data;
    };

    size_t capacity_;
    std::vector<Cell> buffer_;

    std::atomic<size_t> enqueue_pos_;
    std::atomic<size_t> dequeue_pos_;
};