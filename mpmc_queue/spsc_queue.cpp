#include <atomic>
#include <vector>
#include <cstddef>

template <typename T>
class SPSCQueue {
public:
    explicit SPSCQueue(size_t capacity)
        : _capacity(capacity + 1),
          _buffer(_capacity),
          _head(0),
          _tail(0) {}

    bool push(const T& value) {
        size_t tail = _tail.load(std::memory_order_relaxed);
        size_t next = increment(tail);

        if (next == _head.load(std::memory_order_acquire)) {
            return false; // full
        }

        _buffer[tail] = value;

        _tail.store(next, std::memory_order_release);
        return true;
    }

    bool pop(T& value) {
        size_t head = _head.load(std::memory_order_relaxed);

        if (head == _tail.load(std::memory_order_acquire)) {
            return false; // empty
        }

        value = _buffer[head];

        _head.store(increment(head), std::memory_order_release);
        return true;
    }

private:
    size_t increment(size_t index) const {
        return (index + 1) % _capacity;
    }

private:
    const size_t _capacity;
    std::vector<T> _buffer;
    std::atomic<size_t> _head;
    std::atomic<size_t> _tail;
};