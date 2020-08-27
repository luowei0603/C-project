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
    return *this; //���ض���ֵ
}
int main(){
    Point p(1,2);
    ++p; //��ʽ����
    std::cout<<"p.x="<<p.getx()<<",p.y="<<p.gety()<<std::endl;

    p.operator++();  //��ʽ����
    std::cout<<"p.x="<<p.getx()<<",p.y="<<p.gety()<<std::endl;

    return 0;
}
