#include <assert.h>
#include <stdio.h>

#include <iostream>
using namespace std;

#ifdef AC_ENABLE_ASSERT
#define AC_ASSERT(expr)                    \
  do {                                     \
    if (!(expr)) {                         \
      printf("assert failed:%s\n", #expr); \
      assert(0);                           \
    }                                      \
  } while (0)
#else
#define AC_ASSERT(expr)                    \
  do {                                     \
    if (!(expr)) {                         \
      printf("assert failed:%s\n", #expr); \
    }                                      \
  } while (0)
#endif

bool test(int a) {
  std::cout << "this is test, input = " << a << std::endl;
  if (a > 0) return true;
  return false;
}

int main() {
  int a = -5;
  int b = 5;
  AC_ASSERT(test(a));
  printf("hello1\n");
  AC_ASSERT(test(b));
  return 0;
}
