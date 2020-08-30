#ifndef _ALHORITHM_BASE_H
#define _ALGORITHM_BASE_H
class AlgorithmBase{
public:
    AlgorithmBase(){};
    virtual ~AlgorithmBase(){};
    virtual int Sum() = 0;
    virtual int Average() = 0;
    virtual int MaxValue() = 0;
    virtual int MinValue() = 0;
};

// 工厂函数的类型
typedef AlgorithmBase* create_t(int,int);
typedef void destory_t(AlgorithmBase*);
#endif