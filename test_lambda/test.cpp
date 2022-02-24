#include <iostream>
using namespace std;

int main() {
  int a = 5;
  int b = 6;
  int c = 7;
  int arg = 100;
  auto func = [&a, &b, &c, arg](int d) -> int {
    a++;
    b++;
    c++;
    cout << "arg=" << arg << endl;
    return a + b + c + d;
  };
  int d = func(arg);
  int f = [a, b, c](int d) -> int { return a + b + c + d; }(arg);
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "c = " << c << endl;
  cout << "d = " << d << endl;
  cout << "f = " << f << endl;
  return 0;
}
