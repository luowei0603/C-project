#include<iostream>
using namespace std;

class text{
public:
	void print() const {cout << "hello_const" << endl;}
	void print() {cout << "hello" << endl;}

};

int main(){
	const text a;
	text b;
	a.print();
	b.print();
	return 0;
}
