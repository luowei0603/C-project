ubuntu安装libevent
sudo apt-get install libevent-dev
编译
gcc -o test_libevent test_libevent.c -levent
简单的测试libevent添加定时事件
