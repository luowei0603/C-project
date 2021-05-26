#include <ext/hash_map>
#include <iostream>
#include <string>
using namespace std;

int main() {
  __gnu_cxx::hash_map<int, std::string> mymap;
  mymap.insert(std::pair<int, std::string>(3, std::string("luowei")));
  mymap[2] = "yonghong";
  __gnu_cxx::hash_map<int, std::string>::iterator iter = mymap.begin();
  while (iter != mymap.end()) {
    std::cout << iter->first << ":" << iter->second << std::endl;
    iter++;
  }
  return 0;
}
