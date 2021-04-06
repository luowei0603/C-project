#include <iostream>
#include <cmath>
#include <string>
#include "exc_mean.h"

class demo
{
private:
    std::string word;
public:
    demo(const std::string &str) {
        word = str;
        std::cout << "demo " << word << " created\n";
    }
    ~demo() {
        std::cout << "demo " << word << " destoryed\n";
    }
    void show() const{
        std::cout << "demo " << word << " lives!\n";
    }
};

// 前置声明
double hmean(double, double);
double gmean(double, double);
double means(double, double);

int main() {
    using std::cin;
    using std::cout;
    using std::endl;

    double x, y, z;
    demo d1("found in main()");
    cout << "enter two numbers:";
    while (cin >> x >> y)
    {
        try {
            z = means(x, y);
            cout << "The means of " << x << " and " << y << " is " << z << endl;
            cout << "enter next pair: ";
        }
        catch (bad_hmean &bh) {
            bh.mesg();
            cout << "try again.\n";
            continue;
        }
        catch (bad_gmean &bg) {
            cout << bg.mesg();
            cout << " value used: " << bg.v1 << ", " << bg.v2 << endl;
            cout << " sory, you do not get to play any more\n";
            break;
        }
        d1.show();
    }
    cout << "bye" << endl;
    cin.get();
    return 0;
}

double hmean(double a, double b)
{
    if (a == -b) {
        throw bad_hmean(a, b);
    }
    return 2.0 * a * b / (a + b);
}

double gmean(double a, double b)
{
    if (a < 0 || b < 0) {
        throw bad_gmean(a, b);
    }
    return std::sqrt(a * b);
}

double means(double a, double b)
{
    double am, hm, gm;
    demo d2("found in means()");
    am  = (a + b) / 2.0;
    try{
        hm = hmean(a, b);
        gm = gmean(a, b); // 本函数未捕获，会被上一级捕获
    }
    catch (bad_hmean &bh) {
        bh.mesg();
        std::cout << "caught in means()\n";
        throw;  // 扔出去后将会被上一级函数捕获
    }
    d2.show();
    return (am + hm + gm) / 3.0;
}