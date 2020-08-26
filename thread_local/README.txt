在多线程程序中，一个模块里的全局变量，对于该模块的所有线程都是可见的，也就是说全局共享的，
所有线程都可以使用它，可以随时改变它的值，这显然是不安全的，会带来一些风险。
那么有没有什么办法能改善这个问题呢？

pthread_getspecific/pthread_setspecific这两个函数，
其实是属于线程数据存储机制【也叫线程私有数据，英文名Thread Specific Data】的一部分。

应用了线程存储机制之后，这个变量表面上看起来还是一个全局变量，所有线程都可以使用它，
而它的值在每一个线程中又是单独隔离的，彼此之间不会互相影响。A线程对该变量的值进行修改之后，
相应的变化只会在A线程中体现，其他的线程中去查询该变量时，得到的依然是本线程中的值，跟A线程改动的值无关。

线程存储机制的具体用法如下：

1、首先要定义一个类型为pthread_key_t类型的全局变量。
2、调用pthread_key_create()来创建该变量。该函数有两个参数，第一个参数就是上面声明的pthread_key_t变量，第二个参数是一个清理函数，用来在线程释放该线程存储的时候被调用。
该函数指针可以设成NULL，这样系统将调用默认的清理函数。该函数调用成功时返回0，返回其他任何值都表示出现了错误。
3、当线程中需要存储特殊值的时候，可以调用pthread_setspcific()。该函数有两个参数，第一个为前面声明的pthread_key_t变量，第二个为void*变量，这样你可以存储任何类型的值。
4、如果需要取出所存储的值，调用pthread_getspecific()。该函数的参数为前面提到的pthread_key_t变量，该函数返回void *类型的值。
5、注销使用pthread_key_delete()函数，该函数并不检查当前是否有线程正在使用，也不会调用清理函数，而只是释放以供下一次调用pthread_key_create()使用。

下面是前面提到的函数原型：
#include <pthread.h>

int pthread_key_create(pthread_key_t *key, void (*destructor)(void *));
int pthread_key_delete(pthread_key_t *key);
int pthread_setspecific(pthread_key_t key, const void *value);
void *pthread_getspecific(pthread_key_t key);


示例程序中声明了全局变量pthread_key_t p_key，两个线程改变这个全局变量指向的值，两个线程互不干扰。