#include <stdio.h>

int main() {
  char a[6] = "hello";
  printf("a:%s\n", a);
  a[0] = '\0';
  printf("a:%s a[1]=%s\n", a, a + 1);
  a[0] = 0;
  printf("a:%s a[1]=%s\n", a, a + 1);
  return 0;
}
