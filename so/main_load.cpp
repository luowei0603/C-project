#include <iostream>
#include <dlfcn.h>
#include "algorithm_base.h"
using namespace std;

int main()
{
    void *handle;
    int value1, value2;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "please input value1 && value2" << endl;
    cin >> value1 >> value2;

    // 加载库
    handle = dlopen("./libalgorithm.so", RTLD_LAZY);
    if (!handle)
    {
        cerr << "can not open libarary:" << dlerror() << endl;
        return 1;
    }

    // reset errors
    dlerror();

    // 加载符号
    create_t *CreateAlgorithm = (create_t *)dlsym(handle, "create");
    const char *dlsymError = dlerror();
    if (dlsymError)
    {
        cerr << "can not load symbole create:" << dlsymError << endl;
        return 1;
    }

    destory_t *DestoryAlgorithm = (destory_t *)dlsym(handle, "destory");
    dlsymError = dlerror();
    if (dlsymError)
    {
        cerr << "can not load symbole destory:" << dlsymError << endl;
        return 1;
    }

    // 实例化对象
    AlgorithmBase *a = CreateAlgorithm(value1, value2);
    cout << "Sum = " << a->Sum() << endl;
    cout << "Average = " << a->Average() << endl;
    cout << "MaxValue = " << a->MaxValue() << endl;
    cout << "MinValue = " << a->MinValue() << endl;

    // destory对象
    DestoryAlgorithm(a);

    // unload library
    dlclose(handle);

    return 0;
}