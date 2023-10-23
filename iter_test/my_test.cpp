#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> a = {3, 2, 5, 4, 1, 9, 7};
    sort(a.begin(), a.begin() + 3);
    for(int i : a) {
        cout << i << " ";
    }
    cout << endl;
}

// 结果是2 3 5 4 1 9 7 ，也是只有3，2，5参与了排序，因为sort是区间是前闭后开，即[a.begin(), a.begin() + 3)