#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

void *pipe_thread(void *argc) {
  int *fd = (int *)argc;
  int write_fd = *(fd + 1);
  char *p = "test for pipe\n";
  write(write_fd, p, strlen(p));
  return NULL;
}
int main() {
  int fd[2];  // 0是读，1是写
  if (pipe(fd) == -1) {
    std::cout << "pipe error" << std::endl;
  }
  pthread_t tid;
  pthread_create(&tid, NULL, pipe_thread, fd);
  char buf[1024];
  int len = read(fd[0], buf, sizeof(buf));
  printf("read from pipe fd[0]:%d, len:%d\n", fd[0], len);
  std::cout << buf << std::endl;
  pthread_join(tid, NULL);
  return 0;
}
