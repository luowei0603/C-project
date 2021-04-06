#include <iostream>
#include <deque>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
using namespace std;

sem_t bank, goods;
deque<int> my_bank;
void *producer(void *argc)
{
    int i = 0;
    while (1)
    {
        sleep(10);
        sem_wait(&bank);
        my_bank.push_back(i);
        cout << "producer produce a goods:" << i << endl;
        i++;
        sem_post(&goods);
    }
}
void *consumer(void *argc)
{
    while (1)
    {
        sleep(5);
        sem_wait(&goods);
        int tmp = my_bank.front();
        my_bank.pop_front();
        cout << "consumer consume a goods:" << tmp << endl;

        sem_post(&bank);
    }
}
int main()
{
    pthread_t producer_thread, consumer_thread;
    sem_init(&bank, 0, 10);
    sem_init(&goods, 0, 0);
    int ret = 0;
    ret = pthread_create(&producer_thread, NULL, producer, NULL);
    if (ret != 0)
        cout << "create producer thread failed" << endl;
    ret = pthread_create(&consumer_thread, NULL, consumer, NULL);
    if (ret != 0)
        cout << "create consumer thread failed" << endl;
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    sem_destroy(&bank);
    sem_destroy(&goods);
    return 0;
}
