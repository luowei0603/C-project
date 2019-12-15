#include<iostream>
class Point{
private:
    int x;
    int y;
public:
    Point(int xx=0,int yy=0){
        x = xx;
        y = yy;
    }
    int getx(){
        return x;
    }
    int gety(){
        return y;
    }
    Point operator++();
};
Point Point::operator++(){
    ++x;
    ++y;
    return *this; //返回对象值
}
int main(){
    Point p(1,2);
    ++p; //隐式调用
    std::cout<<"p.x="<<p.getx()<<",p.y="<<p.gety()<<std::endl;

    p.operator++();  //显式调用
    std::cout<<"p.x="<<p.getx()<<",p.y="<<p.gety()<<std::endl;

    return 0;
}
