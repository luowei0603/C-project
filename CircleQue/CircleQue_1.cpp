#include<iostream>
#include<vector>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
using namespace std;

template <typename T>
class CirlceQue{
private:
    vector<T> que;
    int capicity;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int head;
    int tail;
  
public:
    CirlceQue(int _capicity): capicity(_capicity), head(0), tail(0) {
        que.reserve(capicity);
        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&cond, NULL);
    }
    ~CirlceQue(){
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
    }
    bool push(T value){
        pthread_mutex_lock(&mutex);
        if ((head + 1) % capicity == tail) { // 队列满了，不允许push
            cout << "push value failed " << value << ", head = " << head 
                 << ", tail = " << tail << endl;
            pthread_mutex_unlock(&mutex);
            return false;
        }
        que[head] = value;
        head = (head + 1) % capicity;
        cout << "push value success " << value << ", head = " << head 
                 << ", tail = " << tail << endl;
        pthread_mutex_unlock(&mutex);
        return true;
    }

    bool pop(T& value){
        pthread_mutex_lock(&mutex);
        if (head == tail) { // 队列空，不允许pop
            cout << "pop value fail " << "65535" << ", head = " << head 
                 << ", tail = " << tail << endl;
            pthread_mutex_unlock(&mutex);
            return false;
        }
        value = que[tail];
        tail = (tail + 1) % capicity;
        cout << "pop value success " << value << ", head = " << head 
                 << ", tail = " << tail << endl;
        pthread_mutex_unlock(&mutex);
        return true;
    }  

    int getHead() {
        return head;
    }  

    int getTail() {
        return tail;
    }
};

void *producer(void *argc) {
    CirlceQue<int>* test = (CirlceQue<int>*) argc;
    for (int i = 0 ; i < 100; i++) {
        test->push(i);
        sleep(rand() % 3);
    }
}

void *consumer(void *argc) {
    CirlceQue<int>* test = (CirlceQue<int>*) argc;
    for (int i = 0 ; i < 100; i++) {
        int ret;
        test->pop(ret);
        sleep(rand() % 3);
    }
}

int main() {
    CirlceQue<int>* test = new CirlceQue<int>(10);
    pthread_t p1, p2, p3, p4;
    // 创建push线程1
    pthread_create(&p1, NULL, producer, test);
    // 创建push线程2
    pthread_create(&p2, NULL, producer, test);
    // 创建pop线程3
    pthread_create(&p3, NULL, consumer, test);
    // 创建pop线程4
    pthread_create(&p4, NULL, consumer, test);
    
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);

    return 0;
}