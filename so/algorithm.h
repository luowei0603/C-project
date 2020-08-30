#ifndef _ALGORITHM_H
#define _ALHORITHM_H
#include "algorithm_base.h"
class Algorithm : public AlgorithmBase {
public:
    Algorithm(int a, int b):value1(a),value2(b){};
    ~Algorithm(){};
    int Sum();
    int Average();
    int MaxValue();
    int MinValue();
private:
    int value1;
    int value2;
};


#endif