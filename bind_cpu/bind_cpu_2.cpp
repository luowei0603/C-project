
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>

#define THREAD_MAX_NUM 200 // CPU核的最大个数
int num = 0;               // CPU核的个数

void *thread_Fun(void *arg)
{
    int *cpu_idx = (int *)arg;
    pthread_t pid = pthread_self();
    cpu_set_t set_mask; // CPU核的集合
    cpu_set_t get_mask; // 获取在集合中的CPU

    printf("thread is:%d\n", *cpu_idx);
    CPU_ZERO(&set_mask);                                         // 置空
    CPU_SET(*cpu_idx, &set_mask);                                // 设置CPU亲和力
    if (pthread_setaffinity_np(pid, sizeof(set_mask), &set_mask) != 0) //设置线程CPU亲和力
    {
        printf("warning: could not set CPU affinity, continuing...\n");
    }

    CPU_ZERO(&get_mask);
    if (pthread_getaffinity_np(pid, sizeof(get_mask), &get_mask) != 0) //获取线程CPU亲和力
    {
        printf("warning: cound not get thread affinity, continuing...\n");
    }

    for (int i = 0; i < num; i++)
    {
        if (CPU_ISSET(i, &get_mask))
        { // 判断线程与哪个CPU有亲和力
            printf("this thread %d is running processor : %d\n", *cpu_idx, i);
        }
    }

    return NULL;
}

int main()
{
    int tid[THREAD_MAX_NUM];
    pthread_t thread[THREAD_MAX_NUM];

    num = sysconf(_SC_NPROCESSORS_CONF); //获取CPU核的个数
    if (num > THREAD_MAX_NUM)
    {
        printf("num of cores[%d] is bigger than THREAD_MAX_NUM[%d]!\n", num, THREAD_MAX_NUM);
        return -1;
    }
    printf("system has %i processor(s). \n", num);

    for (int i = 0; i < num; i++)
    {
        tid[i] = i;
        pthread_create(&thread[i], NULL, thread_Fun, (void *)&tid[i]);
    }

    for (int i = 0; i < num; i++)
    {
        pthread_join(thread[i], NULL);
    }
    return 0;
}