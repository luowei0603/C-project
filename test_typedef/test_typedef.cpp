#include<iostream>
#include<vector>
using namespace std;

typedef vector<int> array;
using array1 = vector<int>;

int main(){
	array a;
	a.push_back(1);
	a.push_back(2);
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	array1 b;
	b.push_back(3);
	b.push_back(4);
	for (int i = 0; i < b.size(); i++) {
		cout << b[i] << " ";
	}
	cout << endl;
	return 0;
}
