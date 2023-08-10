#include <iostream>
#include <string>
// #include <Python.h>
#include <boost/python.hpp> // Boost.Python
// #include <boost/python/detail/wrap_python.hpp>
#include "thread_pool.h"
#include <unistd.h>

boost::python::object hello;
class PyThreadStateLock{
 public:
    PyThreadStateLock() {
        state = PyGILState_Ensure();
    }
    ~PyThreadStateLock() {
        PyGILState_Release(state);
    }
 private:
    PyGILState_STATE state;

};

void c_call_python(int val) {
    // Py_Initialize(); // 初始化 Python 解释器
    
    PyThreadStateLock pylock;
    try
    {
        // 添加模块代码所在路径（Python脚本文件的路径）
       
        // Py_Initialize(); // 初始化 Python 解释器
        
        // 1. 导入模块 hello（hello.py
        // boost::python::object hello = boost::python::import("hello");
        
 
        // 2. 获取属性（函数、类等）
        boost::python::object greeting = hello.attr("greeting");
 
        // 3. 执行Python函数
        boost::python::object res = greeting(val);
        // 其中第2步和第3步可以合并为
        // boost::python::object res = hello.attr("greeting")("2022.04.23");
 
        // 4. 打印返回结果（使用 boost::python::extract 转换）
        std::string tmp = boost::python::extract<std::string>(res);
        // std::cout << tmp << " ... C++" << std::endl;
    }
    catch (const boost::python::error_already_set&)
    {
        PyErr_Print();
        return;
    }
    // Py_Finalize(); // 终止 Python 解释器

}
int main(int argc, char* argv[])
{
    ThreadPool<int>* pool = new ThreadPool<int>(200);
    setenv("PYTHONPATH", ".", 1);
    Py_Initialize(); // 初始化 Python 解释器
    PyEval_InitThreads();
    hello = boost::python::import("hello");
    PyThreadState* py_thread_state_ = PyEval_SaveThread();
    
    for (int i = 0; i < 10000; i++) {
        pool->add_task(c_call_python, i);
    }
    pool->Init();
    
    
    delete pool;
    Py_Finalize(); // 终止 Python 解释器
    
    return 0;
}