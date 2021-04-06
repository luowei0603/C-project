#include<iostream>
#include<string>
using namespace std;

class Destination{
protected:
	string from;
	string to;
public:
	void input(){
		cout<<"please input from:";
		cin>>from;
		cout<<"please input to:";
		cin>>to;
	}
	void output(){
		cout<<"form:"<<from<<" to:"<<to<<endl;
	}
	Destination(string from1="",string to1=""){
		from=from1;
		to=to1;	
	}
}; 

class Time{
protected:
	int h;
	int m;
	int s;
	int ts;
public:
	void input(){
		cout<<"please input comunication time:hour/min/second: ";
		cin>>h>>m>>s;
	}
	void output(){
		ts = h*3600+m*60+s;
		cout<<"comnication time="<<ts<<"s"<<endl;
	}
	Time(int h1=0,int m1=0,int s1=0,int ts1=0){
		h=h1;
		m=m1;
		s=s1;
		ts=ts1;
	}
};

class Price:public Destination,public Time{
private:
	double price;
public:
	Price(string from1,string to1,int h,int m,int s,int ts,double price=0.0):Destination(from1,to1),Time(h,m,s,ts){
	}
	Price(){
	}
	void input1(){
		cout<<"please input destination:"<<endl;
		Destination::input();
		cout<<"please input time:"<<endl;
		Time::input();
	}
	void output1(){
		Destination::output();
		Time::output();
		if(from==to){
			int temp;
			if(ts%10==0){
				temp=ts/10;
			}
			else{
				temp=ts/10+1;
			}
			price=(double)temp*0.06;
		}
		else{
			int temp;
			if(ts%6==0){
				temp=ts/6;
			}
			else{
				temp=ts/6+1;
			}
			price=(double)temp*0.06;
		}
		cout<<"price="<<price<<endl;
	}
	
};

int main(){
	Price a;
	while(1){
		a.input1();
		a.output1(); 
		cout<<"####################"<<endl;
	}
	return 0;
}
