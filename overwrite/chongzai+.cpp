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
    Complex operator+(Complex &c);
    void print();
};
Complex Complex::operator+(Complex &c){
    Complex t;
    t.real = real + c.real;
    t.imag = imag + c.imag;
    return t;
}
void Complex::print(){
    std::cout<<"("<<real<<","<<imag<<")"<<std::endl;
}
int main(){
    Complex a(3.0,4.0),b(10.5,20.5),c;
    c = a + b;
    c.print();
    return 0;
}
