#include "A.h"
#include "B.h"
#include <iostream>
A::A(int val) {
    b = new B();
    this->val = val;
}
A::~A() {
    delete b;
}

void A::print() {
    std::cout << "this is A print:" << std::endl;
    b->print(this);
}