#include <memory>

using namespace std;

class control_block {
 private:
  atomic_int cnt;

 public:
  control_block(int i = 0) : cnt(i){};

  void add() { cnt++; }

  void sub() { cnt--; }

  size_t getCnt() { return cnt; }
};

template <class T>
class my_shared_ptr {
 private:
  T *m_ptr;
  control_block *ctrl_blk;

  void release() {
    ctrl_blk->sub();
    if (ctrl_blk->getCnt() == 0) {
      delete ctrl_blk;
      delete m_ptr;
      ctrl_blk = nullptr;
      m_ptr = nullptr;
    }
  }

 public:
  //默认构造
  // ctrl_blk(nullptr)  异常 my_shared_ptr<int> x, y(new int(2)); x = y;
  my_shared_ptr() : m_ptr(nullptr), ctrl_blk(new control_block){};

  //有参构造
  explicit my_shared_ptr(T *ptr) : m_ptr(ptr), ctrl_blk(new control_block(1)) {}

  //拷贝构造
  my_shared_ptr(const my_shared_ptr &ptr) {
    ctrl_blk = ptr.ctrl_blk;
    m_ptr = ptr.m_ptr;
    ctrl_blk->add();
  }

  my_shared_ptr(my_shared_ptr &&ptr) noexcept
      : m_ptr(ptr.m_ptr), ctrl_blk(ptr.ctrl_blk) {
    ptr.m_ptr = nullptr;
    ptr.ctrl_blk = nullptr;
  }

  //赋值
  my_shared_ptr &operator=(const my_shared_ptr &ptr) {
    // 避免自我赋值
    if (this == &ptr) {
      return *this;
    }
    release();
    ctrl_blk = ptr.ctrl_blk;
    ctrl_blk->add();
    m_ptr = ptr.m_ptr;
    return *this;
  }

  //析构
  ~my_shared_ptr() { release(); }

  //返回引用计数
  size_t use_count() { return ctrl_blk->getCnt(); }

  //*解引用
  T &operator*() { return *m_ptr; }

  //->
  T &operator->() { return m_ptr; }
};

int main() {
  my_shared_ptr<int> x, y(new int(2));
  x = y;
  return 0;
}
