#include <memory>
class SharedPtrControlBlock {
  template <typename T>
  friend class shared_ptr;
  template <typename T>
  friend class weak_ptr;

 private:
  SharedPtrControlBlock() : ref_count_(1), weak_count_(1) {}
  atomic<int> ref_count_;
  atomic<int> weak_count_;
};

template <typename T>
class shared_ptr {
 public:
  explicit shared_ptr(T* ptr = nullptr)
      : ptr_(ptr), control_block_(new SharedPtrControlBlock) {}
  shared_ptr(const shared_ptr<T>& ptr)
      : ptr_(nullptr), control_block_(nullptr) {
    Initialize(ptr);
  }
  shared_ptr<T>& operator=(const shared_ptr<T>& ptr) {
    if (this != &ptr) {
      shared_ptr<T> me(ptr);
      swap(me);
    }

    return *this;
  }
  shared_ptr(shared_ptr<T>&& ptr) {
    ptr_ = ptr.ptr_;
    ptr.ptr_ = nullptr;

    control_block_ = ptr.control_block_;
    ptr.control_block_ = nullptr;
  }

  ~shared_ptr() {
    if (ptr_ != nullptr) {
      if (--control_block_->ref_count_ <= 0) {
        delete ptr_;
        if (--control_block_->weak_count_ <= 0) {
          delete control_block_;
        }
      }
    }
  }

  void swap(shared_ptr<T>& ptr) {
    std::swap(ptr_, ptr.ptr_);
    std::swap(control_block_, ptr.control_block_)
  }

  T* get() { return ptr_; }
  T& operator*() { return *ptr_; }
  int use_count() { return control_block_->ref_count_; }

 private:
  void Initialize(shared_ptr<T>& ptr) {
    if (ptr.ptr_ != nullptr) {
      ++ptr.control_block_->ref_count_;

      ptr_ = ptr.ptr_;
      control_block_ = ptr.control_block_;
    }
  }

 private:
  T* ptr_;
  SharedPtrControlBlock* control_block_;
};

template <typename T>
class weak_ptr {
 public:
  weak_ptr() : ptr_(nullptr), control_block_(nullptr) {}
  weak_ptr(const weak_ptr<T>& ptr) {
    ptr_ = ptr;
    control_block_ = ptr.control_block_;
    ++control_block_->weak_count;
  }
  weak_ptr<T>& operator=(const weak_ptr<T>& ptr) {
    if (this != &ptr) {
      weak_ptr<T> me(ptr);
      std::swap(ptr_, me.ptr_);
      std::swap(control_block_, me.control_block_);
    }

    return *this;
  }
  ~weak_ptr() {
    if (ptr_ != nullptr) {
      if (--control_block_->weak_count_ <= 0) {
        delete control_block_;
      }
    }
  }

  int use_count() const { return control_block_->ref_count_; }
  bool expired() const { return control_block_->ref_count_ == 0; }

 private:
  T* ptr_;
  SharedPtrControlBlock* control_block_;
};