#include <stdio.h>

void Tp(unsigned long *value)
{
    *value = 20;
    return;
}

void GetType(char *type)
{
    *type = 10;
    Tp(type);
    return;
}

int Test()
{
    char type = 0;
    GetType(&type);
    printf("type = %d\n", type);
    return 0;
}

int main()
{
    int tmp;
    int ret;
    ret = Test();
    return 0;
}