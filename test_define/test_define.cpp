#include <iostream>
using namespace std;
#define Add(a, b, sum)        \
  do {      /*just for test*/ \
    sum =   /*just for test*/ \
        a + /*just for test*/ \
        b;  /*just for test*/ \
  } while (0);
#define Add2(a, b, sum) /*just for test*/ \
  {                     /*for test*/      \
    sum =               /*just for test*/ \
        a + 1           /*test*/          \
        + b             /*test*/          \
        + 1             /*test*/          \
        ;               /*test*/          \
  }

int main() {
  int a, b = 0;
  cin >> a;
  cin >> b;
  int sum = 0;
  Add(a, b, sum);
  cout << sum << endl;
  Add2(a, b, sum);
  cout << sum << endl;
  return 0;
}
