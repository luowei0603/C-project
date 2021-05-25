#include <cxxabi.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <sstream>

static char *get_sig_str(int sig) {
  switch (sig) {
    case SIGINT:
      return "SIGINT";
    case SIGABRT:
      return "SIGABRT";
    case SIGSEGV:
      return "SIGSEGV";
    case SIGTERM:
      return "SIGTERM";
  }
  return "error";
}

static int create_stak_file() {
  int stack_fd = -1;
  std::string log_path = GlobalConfSingleton::GetInstance().getAcConf().global.log_path;
  if (access(log_path.c_str(), F_OK) != 0) {
    if (mkdir(log_path.c_str(), 0777) != 0) {
      slog_write(LL_FATAL, "create dir failed:%s", log_path.c_str());
      return stack_fd;
    }
  }
  log_path += "/stack_log";
  if (access(log_path.c_str(), F_OK) != 0) {
    if (mkdir(log_path.c_str(), 0777) != 0) {
      slog_write(LL_FATAL, "create dir failed:%s", log_path.c_str());
      return stack_fd;
    }
  }

  // 堆栈日志名中包含当前时间 + pid
  std::stringstream file_name;
  pid_t pid = getpid();
  file_name << log_path.c_str() << "/ac_";
  time_t tt = time(NULL);
  tm *t = localtime(&tt);
  file_name << t->tm_year + 1900 << t->tm_mon + 1 << t->tm_mday << "_"
            << t->tm_hour << "_" << t->tm_min << "_" << t->tm_sec <<"_" << pid << "_new.log";

  stack_fd = open(file_name.str().c_str(), O_RDWR | O_CREAT, 0644);
  if (stack_fd <= 0) {
    slog_write(LL_FATAL, "open file error:%s", file_name.str().c_str());
  }
  return stack_fd;
}

static void dump_stack() {
  int stack_fd;
  char **symbols;
  void *stack[100];  // 数组大小代表最多可以打印的堆栈信息层数
  stack_fd = create_stak_file();
  if (stack_fd <= 0) {
    return;
  }
  int size = backtrace(stack, 100);
  // backtrace_symbols_fd(stack, size, stack_fd);
  symbols = backtrace_symbols(stack, size);  // 获取堆栈符号
  if (!symbols) {
    slog_write(LL_FATAL, "backtrace_symbols return null");
    close(stack_fd);
    return;
  }
  for (int i = 0; i < size; i++) {  // 根据符号获取函数名并dump到文件
    const char *mangledName = NULL;
    const char *cxaDemangled = NULL;
    mangledName = symbols[i];
    Dl_info info;
    if (dladdr(stack[i], &info) && info.dli_sname) {  // 根据符号找到地址
      mangledName = info.dli_sname;
    }
    if (mangledName) {
      int status = 0;
      cxaDemangled = abi::__cxa_demangle(mangledName, NULL, NULL, &status);
    }
    if (mangledName || cxaDemangled) {
      std::stringstream out;
      out << "#" << i << "\t" << stack[i] << "\t"
          << (cxaDemangled ? cxaDemangled : mangledName) << std::endl;
      write(stack_fd, out.str().c_str(), out.str().size());
    }
  }
  free(symbols);
  close(stack_fd);
  return;
}

static void sig_handler(int signo) {
  char *sigstr = get_sig_str(signo);
  slog_write(LL_NOTICE, "server exit %d:%s", signo, sigstr);
 
  switch (signo) {
    case SIGTERM:
      suicide();
      break;
    case SIGINT:
      suicide();
      break;
    case SIGSEGV:
      dump_stack();
      raise(signo);
      break;
    case SIGABRT:
      dump_stack();
      raise(signo);
      break;
    default:
      slog_write(LL_NOTICE, "sig_handler error signo:%d", signo);
      break;
  }

  return;
}

static void signal_init() {
  signal(SIGTERM, sig_handler);
  signal(SIGINT, sig_handler);
  signal(SIGCHLD, SIG_IGN);
  signal(SIGPIPE, SIG_IGN);

  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = sig_handler;
  sa.sa_flags = SA_RESETHAND;
  sigemptyset(&sa.sa_mask);

  if (sigaction(SIGSEGV, &sa, NULL) < 0) {
    fprintf(stderr, "sigaction SIGSEGV failed:%s", strerror(errno));
    suicide();
  }
  if (sigaction(SIGABRT, &sa, NULL) < 0) {
    fprintf(stderr, "sigaction SIGABRT failed:%s", strerror(errno));
    suicide();
  }

  return;
}
