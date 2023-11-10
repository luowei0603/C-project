#include <iostream>

class A {
public:
    A() {
        std::cout << "调用构造函数" << std::endl;
    }
    ~A() {
        std::cout << "调用析构函数" << std::endl;
    }
    A(const A& other) {
        std::cout << "调用拷贝构造函数" << std::endl;
    }
     A(A&& other) {
         std::cout << "调用移动构造函数" << std::endl;
     }
    A& operator=(const A& other) {
        std::cout << "调用拷贝赋值运算符" << std::endl;
        return *this;
    }
     A&& operator=(A&& other) {
         std::cout << "调用移动赋值运算符" << std::endl;
	return std::move(*this);
     }

};

A GetA() {
    A a;
    return std::move(a);
    // return a;
}

int main() {
    A a;
    // A b = std::move(a);
    a = GetA();
   
    return 0;
}
