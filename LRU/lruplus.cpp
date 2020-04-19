#include <iostream>
#include <map>
#include <list>
#define INVALID 65535
/*lru 模板*/
using namespace std;
template <typename T, typename V>
struct Node
{
    T key;
    V value;
    Node(T _key, V _value) : key(_key), value(_value) {}
};

template <typename T, typename V>
class LruCache
{
private:
    int capicity; // LruCache的容量
    list<Node<T, V>> LruList;
    map<T, typename list<Node<T, V>>::iterator> LruMap; // 这里加typename关键字，是为了声明这是::iterator是一个迭代器类型不是某个类的成员变量

public:
    LruCache(int c) : capicity(c) {}
    V get(T key)
    {
        if (LruMap.find(key) == LruMap.end())
        { //没有找到
            cout << "key (" << key << ") not in memory,value:";
            return INVALID;
        }
        // 将该node放到list的头部
        LruList.splice(LruList.begin(), LruList, LruMap[key]);
        LruMap[key] = LruList.begin();
        return LruMap[key]->value;
    }
    void set(T key, V value)
    {
        if (LruMap.find(key) == LruMap.end())
        {
            // LruCache的容量满了，需要把list末尾的删掉
            if (LruMap.size() == capicity)
            {
                LruMap.erase(LruList.back().key);
                LruList.pop_back();
            }
            LruList.push_front(Node<T, V>(key, value));
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
    LruCache<int, int> lc(10);
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