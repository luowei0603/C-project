#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

int main() {
  int fd[2];  // 0是读，1是写
  if (pipe(fd) == -1) {
    std::cout << "pipe error" << std::endl;
  }
  char *p = "test for pipe\n";
  pid_t pid;
  pid = fork();
  if (pid < 0) {
    std::cout << "fork error" << std::endl;
    exit(1);
  } else if (pid == 0) {  // 子进程
    char buf[1024];
    int len = read(fd[0], buf, sizeof(buf));
    printf("read from pipe fd[0]:%d, len:%d\n", fd[0], len);
    std::cout << buf << std::endl;
  } else {
    write(fd[1], p, strlen(p));
    wait(NULL);  // 等待子进程结束
  }
  return 0;
}
