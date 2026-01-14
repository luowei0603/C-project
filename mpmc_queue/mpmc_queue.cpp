#include "mpmc_queue.h"

template<typename T>
bool MPMCQueue<T>::enqueue(const T& data) {
    Cell* cell;
    size_t pos = enqueue_pos_.load(std::memory_order_relaxed);

    while (true) {
        cell = &buffer_[pos & (capacity_ - 1)];
        size_t seq = cell->sequence.load(std::memory_order_acquire);
        intptr_t diff = (intptr_t)seq - (intptr_t)pos;

        if (diff == 0) {
            // 尝试抢占这个位置
            if (enqueue_pos_.compare_exchange_weak(
                    pos, pos + 1,
                    std::memory_order_relaxed)) {
                break;
            }
        } else if (diff < 0) {
            // 队列满
            return false;
        } else {
            pos = enqueue_pos_.load(std::memory_order_relaxed);
        }
    }

    cell->data = data;
    cell->sequence.store(pos + 1, std::memory_order_release);
    return true;
}

template<typename T>
bool MPMCQueue<T>::dequeue(T& data) {
    Cell* cell;
    size_t pos = dequeue_pos_.load(std::memory_order_relaxed);

    while (true) {
        cell = &buffer_[pos & (capacity_ - 1)];
        size_t seq = cell->sequence.load(std::memory_order_acquire);
        intptr_t diff = (intptr_t)seq - (intptr_t)(pos + 1);

        if (diff == 0) {
            // 尝试消费
            if (dequeue_pos_.compare_exchange_weak(
                    pos, pos + 1,
                    std::memory_order_relaxed)) {
                break;
            }
        } else if (diff < 0) {
            // 队列空
            return false;
        } else {
            pos = dequeue_pos_.load(std::memory_order_relaxed);
        }
    }

    data = cell->data;
    cell->sequence.store(pos + capacity_, std::memory_order_release);
    return true;
}

