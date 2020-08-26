#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

pthread_key_t p_key;

void *thread_func1(void *args)
{
    int count = 5;
    while (count > 0) {
        pthread_setspecific(p_key, args);

        int *tmp1 = (int *)pthread_getspecific(p_key);
        printf("pthread %ld get specific_data %d\n", pthread_self(), *tmp1);
        *tmp1 = *tmp1 + 1;
        printf("pthread %ld change specific_data to %d\n", pthread_self(), *tmp1);

        int *tmp2 = (int *)pthread_getspecific(p_key);
        printf("pthread %ld get specific_data %d\n", pthread_self(), *tmp2);
        sleep(1);
        count--;
    }

}

void *thread_func2(void *args)
{
    
    int count = 5;
    while (count > 0) {
        pthread_setspecific(p_key, args);

        int *tmp1 = (int *)pthread_getspecific(p_key);
        printf("pthread %ld get specific_data %d\n", pthread_self(), *tmp1);
        *tmp1 = *tmp1 + 2;
        printf("pthread %ld change specific_data to %d\n", pthread_self(), *tmp1);

        int *tmp2 = (int *)pthread_getspecific(p_key);
        printf("pthread %ld get specific_data %d\n", pthread_self(), *tmp2);
        sleep(1);
        count--;
    }

}

int main()
{
    int value1 = 0;
    int value2 = 0;
    pthread_t t1, t2;

    pthread_key_create(&p_key, NULL);
    pthread_create(&t1, NULL, thread_func1, &value1);
    pthread_create(&t2, NULL, thread_func2, &value2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("at last: value1 = %d, value2 = %d\n", value1, value2);
    return 0;
}
