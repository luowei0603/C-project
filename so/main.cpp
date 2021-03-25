#include <iostream>
#include "algorithm.h"
using namespace std;
int main()
{
    int value1;
    int value2;
    cout << "please input value1 && value2:" << endl;
    cin >> value1 >> value2;
    AlgorithmBase *a = new Algorithm(value1, value2);
    cout << "Sum = " << a->Sum() << endl;
    cout << "Average = " << a->Average() << endl;
    cout << "MaxValue = " << a->MaxValue() << endl;
    cout << "MinValue = " << a->MinValue() << endl;
    return 0;
}