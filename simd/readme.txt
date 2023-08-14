simd指令测试，参考网页：https://zhuanlan.zhihu.com/p/416172020
一个普通加法指令，一次只能对两个数执行一个加法操作。
一个 SIMD 加法指令，一次可以对两个数组（向量）执行加法操作。
-mavx512f 表示使用 AVX512 指令集。如果 CPU 不支持 AVX512，可以使用其它 SIMD 指令集。相关编译选项有：
-mmmx、-msse、-msse2、-msse3、-mssse3、-msse4.1、-msse4.2、-msse4、-mavx、-mavx2、-mavx512f、-mavx512pf、
-mavx512er、-mavx512cd、-mavx512vl、-mavx512bw、-mavx512dq、-mavx512ifma、-mavx512vbmi。
编译
g++ -o built-vec -mmmx -std=c++11 simd.cpp
运行结果
v0: [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
v1: [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ]
v0 = v0 + 1: [ 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ]
v1 = v1 + 2: [ 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 ]
v0 = v0 + v1: [ 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 ]
v1 = v0 * v1: [ 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 ]
c = a > b: [ 0 0 0 0 0 -1 -1 -1 -1 0 0 0 0 0 0 0 ]
d = (a > b) ? v0 : v1: [ 6 6 6 6 6 3 3 3 3 6 6 6 6 6 6 6 ]
