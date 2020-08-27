/*表驱动简单示例2019.12.08*/
#include<iostream>
using namespace std;
enum msg_type{
    MSG_A,
    MSG_B,
    MSG_C,
};

void processMsgA(){
    cout<<"this is MsgA"<<endl;
}

void processMsgB(){
    cout<<"this is MsgB"<<endl;
}

void processMsgC(){
    cout<<"this is MsgC"<<endl;
}

typedef struct msg_item_s{
    int msg;
    void(*processMsg)();
}msg_item_t;

static const msg_item_t g_msg_items[]={
    {MSG_A,processMsgA},
    {MSG_B,processMsgB},
    {MSG_C,processMsgC}
};

void msgProcess(int msg){
    int num_items = sizeof(g_msg_items)/sizeof(g_msg_items[0]);
    for(int i=0;i<num_items;i++){
        if(g_msg_items[i].msg==msg)
        {
            g_msg_items[i].processMsg();
            break;
        }
    }
}
int main(){
    msgProcess(MSG_B);
    return 0;
}
