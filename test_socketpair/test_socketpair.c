#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>

#define SOCKET_BUFFER_SIZE 10000

void *thread_func(void *argv) {
    int len = 0;
    int fd = *(int *)(argv);
    char buf[500];
    int cnt = 0;

    while(1) {
        len = sprintf(buf, "Hi, main, cnt = %d", cnt++);
        write(fd, buf, len);

        len = read(fd, buf, 500);
        buf[len] = '\0';
        printf("recv info from main:%s\n", buf);

        sleep(5);
    }
    return NULL;   
}

int main() {
    int ret;
    int sockets[2];
    int bufferSize = SOCKET_BUFFER_SIZE;
    pthread_t thread;

    // ret = socketpair(AF_UNIX, SOCK_SEQPACKET, 0, sockets);
    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
    if (ret == -1) {
        printf("socketpair create error!\n");
        return -1;
    }

    // 设置socket描述符的选项
    // setsockopt(sockets[0], SOL_SOCKET, SO_SNDBUF, &bufferSize, sizeof(bufferSize));
    // setsockopt(sockets[0], SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));
    // setsockopt(sockets[1], SOL_SOCKET, SO_SNDBUF, &bufferSize, sizeof(bufferSize));
    // setsockopt(sockets[1], SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

    pthread_create(&thread, NULL, thread_func, (void*)(&sockets[1]));

    int len = 0;
    int fd = sockets[0];
    char buf[500];
    int cnt = 0;

    while(1) {
        len = read(fd, buf, 500);
        buf[len] = '\0';
        printf("recv info from thread:%s\n", buf);

        len = sprintf(buf, "Hi, thread, cnt = %d", cnt++);
        write(fd, buf, len);
    }
    
    pthread_join(thread, NULL);
    return 0;
}