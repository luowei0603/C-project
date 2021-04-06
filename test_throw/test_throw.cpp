#include <iostream>

int func(int a, int b)
{
    if (b == 0)
    {
        throw "zero can not be chu";
    }
    return a / b;
}

int main()
{
    int a, b, c;
    while (std::cin >> a >> b)
    {
        try
        {
            c = func(a, b);
        }
        catch (const char *s)
        {
            std::cout << s << std::endl;
            std::cout << "please input a & b" << std::endl;
            continue;
        }
        std::cout << "ans is: " << c << std::endl;
    }
    return 0;
}