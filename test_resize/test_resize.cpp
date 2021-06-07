#include<iostream>
#include<string>
using namespace std;
int main(){
	string a("hello world luowei");
	a.resize(5);
	a.append("hello world luowei");
	cout << a << endl;
	string b("hello world luowei");
	b.resize(100);
	b.append("hello world luowei");
	cout << b << endl;
	return 0;
}
