#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() {
    #pragma omp parallel for num_threads(2)
    for (int i = 0; i < 12; i++) {
        printf("openmo test, 线程编号：%d\n", omp_get_thread_num);
    }
    return 0;
}