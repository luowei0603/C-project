//#define NDEBUG
#include<iostream>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<execinfo.h>
#include<cassert>
#include<string.h>

int g_fd;

void my_assert(bool check) {
	assert(check);
	return;
}
void signal_handler(int signo) {
	if (signo == SIGSEGV || signo == SIGABRT) {
		void *stack[200];
		int size = backtrace(stack, 200);
		backtrace_symbols_fd(stack, size, g_fd);
		raise(signo);
	}
	return;
}
void signal_init() {
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESETHAND;
	if (sigaction(SIGSEGV, &sa, NULL) < 0) {
		std::cout << "sigaction failed:%s" << strerror(errno);
		exit(1);
	}
	if (sigaction(SIGABRT, &sa, NULL) < 0) {
		std::cout << "sigaction failed:%s" << strerror(errno);
	        exit(1);
	}
	return;
}

void input() {
       int a;
       std::cout << "please input:" << std::endl;
       std::cin >> a;
       assert(a < 10);
       int *b;
       *b = a;
       return;
}

int main() {
	g_fd = open("stack.log", O_RDWR|O_CREAT, 0777);
	signal_init();
	input();
	return 0;
}
