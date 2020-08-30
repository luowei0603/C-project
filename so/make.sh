rm *.so
g++ algorithm.cpp -fPIC -shared -o libalgorithm.so
g++ -o main main.cpp -L. -lalgorithm
export LD_LIBRARY_PATH=.  
./main

g++ -o main_load main_load.cpp -ldl
./main_load