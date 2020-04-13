#include <iostream>
#include <map>
#include <list>
#define INVALID 65535

using namespace std;

struct Node
{
    int key;
    int value;
    Node(int _key, int _value) : key(_key), value(_value) {}
};

class LruCache
{
private:
    int capicity; // LruCache的容量
    list<Node> LruList;
    map<int, list<Node>::iterator> LruMap;

public:
    LruCache(int c) : capicity(c) {}
    int get(int key)
    {
        if (LruMap.find(key) == LruMap.end())
        { //没有找到
            cout << "not find key in memory: " << key << " ";
            return INVALID;
        }
        // 将该node放到list的头部
        LruList.splice(LruList.begin(), LruList, LruMap[key]);
        LruMap[key] = LruList.begin();
        return LruMap[key]->value;
    }
    void set(int key, int value)
    {
        if (LruMap.find(key) == LruMap.end())
        {
            // LruCache的容量满了，需要把list末尾的删掉
            if (LruMap.size() == capicity)
            {
                LruMap.erase(LruList.back().key);
                LruList.pop_back();
            }
            LruList.push_front(Node(key, value));
            LruMap[key] = LruList.begin();
        }
        else
        {
            LruMap[key]->value = value;                            //更新值
            LruList.splice(LruList.begin(), LruList, LruMap[key]); //移到链表头部
            LruMap[key] = LruList.begin();
        }
    }
};

int main()
{
    LruCache lc(10);
    for (int i = 0; i < 10; i++)
    {
        lc.set(i, i);
    }
    for (int i = 0; i < 10; i++)
    {
        cout << lc.get(i) << " ";
    }
    cout << endl;
    cout << "after Inserting (10,10):" << endl;
    lc.set(10, 10);
    for (int i = 0; i <= 10; i++)
    {
        cout << lc.get(i) << " ";
    }
    cout << endl;
    cout << "after Inserting (11,11):" << endl;
    lc.set(11, 11);
    for (int i = 0; i <= 11; i++)
    {
        cout << lc.get(i) << " ";
    }
    cout << endl;
    return 0;
}