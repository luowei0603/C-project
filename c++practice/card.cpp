/* 银行卡交易系统 2019.12.08*/
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

class Card{
private:
    vector<int> money;
    vector<string> time;
    vector<int> rest;
    static int sum;
public:
    Card();
    ~Card();
    void CardIn(int,char*);
    void CardOut(int,char*);
    void ShowRecord();
};

int Card::sum=0; //静态变量，记录当前余额

Card::Card(){
    cout<<"call constriction"<<endl;
}

Card::~Card(){
    cout<<"call destory constriction"<<endl;
}

void Card::CardIn(int _money,char *_time){
    string s_time(_time);
    time.push_back(s_time);
    money.push_back(_money);
    sum += _money;
    rest.push_back(sum);
}
void Card::CardOut(int _money,char *_time){
    if(_money>sum){
        cout<<"当前余额为："<<sum<<"余额不足"<<endl;
    }
    else{
        string s_time(_time);
        time.push_back(s_time);
        money.push_back(-_money);
        sum -= _money;
        rest.push_back(sum);
    }
}
void Card::ShowRecord(){
    int recordNum=time.size();
    cout<<"  日期       存入       取出        余额 "<<endl;
    for(int i=0;i<recordNum;i++){
        cout<<time[i]<<setw(10);
    if(money[i]>=0){
        cout<<money[i]<<setw(20);
    }
    else{
        cout<<setw(20)<<-money[i]<<setw(10);
    }
    cout<<rest[i]<<endl;
    }
}

int main(){
    Card luowei;
    luowei.CardIn(10000,"2009.01.07");
    luowei.CardOut(20000,"2009.01.08");
    luowei.CardIn(5000,"2019.09.07");
    luowei.CardOut(2000,"2019.10.26");
    luowei.ShowRecord();
    return 0;
}
