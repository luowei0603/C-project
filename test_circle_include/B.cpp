#include "B.h"
#include "A.h"
#include <iostream>
void B::print(A *a) {
    std::cout << "this is B print: " << a->val << std::endl;
}
