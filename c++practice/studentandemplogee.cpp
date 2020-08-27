#include<iostream>
#include<string.h>

class Date{
protected:
	int year;
	int month;
	int day;
public:
	Date(int x=0,int y=0,int z=0):year(x),month(y),day(z){		
	};
	void showDate(); 
};
void Date::showDate(){
	std::cout<<"birthdate:"<<year<<"."<<month<<"."<<day<<std::endl;
} 

class Person{
protected:
	char name[255];
	int sex;//0ÄÐ£¬1Å®
	Date birthdate; 
public:
	Person(char _name[255], int _sex, int x, int y, int z); 
	void showinfo(){
		std::cout<<name<<std::endl;
		std::cout<<sex<<std::endl;
		birthdate.showDate();
	}
};
Person::Person(char _name[255], int _sex, int x, int y, int z):birthdate(x,y,x)
{
	strcpy(name,_name);
	sex=_sex;
} 

class Student: public Person{
private:
	int schoolnum;
	double grade;
	static int count;
	static double totalgrade;
public:
	Student(char _name[255], int _sex, int x, int y, int z,int _schoolnum,double _grade);
	static void showaveragegrade();
	~Student();
	void showstudentinfo(){
		showinfo();
		std::cout<<"schoolnum num: "<<schoolnum<<std::endl;
		std::cout<<"grade: "<<grade<<std::endl; 
	}
		
};
Student::Student(char _name[255], int _sex, int x, int y, int z,int _schoolnum,double _grade):Person(_name,sex,x,y,z)
{
	schoolnum=_schoolnum;
	grade=_grade;
	count++;
	totalgrade = totalgrade + _grade;	
}
Student::~Student(){
	count--;
	totalgrade=totalgrade-grade;
}
void Student::showaveragegrade(){
	std::cout<<"total student num = "<<count<<std::endl; 
	std::cout<<"average grade = "<<totalgrade/(double)count<<std::endl;
}
int Student::count = 0;
double Student::totalgrade = 0.0;

class Employee: public Person{
private:
	int worknum;
	double money;
	static int count;
	static double totalmoney;
public:
	Employee(char _name[255], int _sex, int x, int y, int z,int _worknum,double _money); 
	static void showaveragemoney();
	~Employee();
	void showemployeeinfo(){
		Person::showinfo();
		std::cout<<"work num: "<<worknum<<std::endl;
		std::cout<<"money: "<<money<<std::endl; 
	}
	
};
Employee::Employee(char _name[255], int _sex, int x, int y, int z,int _worknum,double _money):Person(_name,sex,x,y,z)
{
	worknum=_worknum;
	money= _money;
	count++;
	totalmoney=totalmoney+_money;
}
Employee::~Employee(){
	count--;
	totalmoney=totalmoney-money;
}
void Employee::showaveragemoney(){
	std::cout<<"total worker num = "<<count<<std::endl;
	std::cout<<"average money ="<<totalmoney/(double)count<<std::endl;
}
int Employee::count = 0;
double Employee::totalmoney = 0.0;
int main(){

	Student a("ÍõÓêÇç",1,1995,7,1,20141234,97.0);
	a.showstudentinfo();
	Student b("Ì·ÓÀºì",1,1995,8,9,20144567,96.0);
	b.showstudentinfo();
	Student::showaveragegrade();
	Employee c("ÂÞÍþ",0,1994,6,3,00517410,14000.0);
	c.showemployeeinfo();
	Employee d("Íõ°Ëµ°",1,1994,8,9,002323,15000.0);
	d.showemployeeinfo(); 
	Employee::showaveragemoney();
	
	return 0; 
}



