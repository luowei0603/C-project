#include "algorithm.h"

int Algorithm::Sum()
{
    return value1 + value2;
}

int Algorithm::Average()
{
    return (value1 + value2) / 2;
}

int Algorithm::MaxValue()
{
    return value1 > value2 ? value1 : value2;
}

int Algorithm::MinValue()
{
    return value1 < value2 ? value1 : value2;
}

// 类工厂，用来构造对象
extern "C" AlgorithmBase *create(int value1, int value2)
{
    return new Algorithm(value1, value2);
}

extern "C" void destory(AlgorithmBase *a)
{
    delete a;
}