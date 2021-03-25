#include<iostream>
class Complex{
private:
    double real;
    double imag;
public:
    Complex(double x=0.0,double y=0.0){
        real = x;
        imag = y;
    }
    friend Complex operator+(Complex &x,Complex &y);
    void print();
};
Complex operator+(Complex &x,Complex &y){
    Complex t;
    t.real = x.real + y.real;
    t.imag = x.imag + y.imag;
    return t;
}
void Complex::print(){
    std::cout<<"("<<real<<","<<imag<<")"<<std::endl;
}

int main(){
    Complex a(3.0,4.0),b(10.5,20.5),c,d;
    c = a + b; //隐式调用
    c.print();
    d = operator+(a,b);   //显式调用
    d.print();
    return 0;
}
