    为了学习动态库而做的小练习，用两种方式加载动态库，一个是编译时候指明动态库，另一种方法是在代码内部加载，关于第二
种方法是在工作的时候，有项目中用了这种方法，项目中通过xml配置文件指定动态库的名字，在程序运行时候读配置文件，然后加载
对应的动态库，这样做的好处是不需要再次编译源码。
    本项目是C++代码，包含两个类，纯虚基类AlgorithmBase和类Algorithm,主要实现了整数求和、求平均、求最大最小值的简单的
运算。
    main.cpp是在编译可执行文件时链接指定要链接的动态库，main_load.cpp是在代码内部运行的时候加载动态库。
    make.sh是编译运行脚本。
    第一种方式没说明好说的，动态库的基本操作。直接看第二种方法。
    这里在基类AlgorithmBase中定义了两个函数类型，create_t和destory_t，在so的algorithm.cpp中定义了工厂函数，用来new和delete
对象。在main_load.cpp，主函数运行加载符号时返回creat_t和destory_t类型的那两个工厂函数。之所以这么做，是因为dlsym本身是用于
C语言的，不支持返回类，所以才需要工厂函数，工厂函数按照C的风格编译，可以正常返回符号。
参考：https://www.cnblogs.com/joeblackzqq/archive/2011/03/30/2000209.html
    https://blog.csdn.net/bailyzheng/article/details/17613847


