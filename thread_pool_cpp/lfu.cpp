#include <iostream>
#include <set>
#include <unordered_map>
using std::set;
using std::unordered_map;
using namespace std;
class Node {
public:
    int key;
    int value;
    int time;
    int cnt;
    Node(){}
    Node(int _key, int _value, int _time, int _cnt): key(_key), value(_value), time(_time), cnt(_cnt) {}
    bool operator<(const Node& other) const {
        return cnt == other.cnt ? time < other.time : cnt < other.cnt;
    }
};
class LFUCache {
public:
    unordered_map<int, Node> lfu_hash;
    set<Node> lfu_set;
    int capacity;
    int time;
    LFUCache(int capacity) {
        this->capacity = capacity;
        lfu_hash.clear();
        lfu_set.clear();
        time = 0;
    }
    
    int get(int key) {
        if (lfu_hash.count(key)) {
            auto node = lfu_hash[key];
            lfu_set.erase(node);
            node.cnt++;
            node.time = time++;
            lfu_set.insert(node);
            lfu_hash[key] = node;
            return node.value;
        }
        return -1;

    }
    
    void put(int key, int value) {
        if (!capacity) {
            return;
        }
        if (lfu_hash.count(key) == 0) {
            if (lfu_set.size() == capacity) {
                auto node = lfu_set.begin();
                lfu_hash.erase(node->key);
                lfu_set.erase(node); 
            }
            Node node(key, value, time++, 1);
            lfu_hash[key] = node;
            lfu_set.insert(node);
        } else {
            auto node = lfu_hash[key];
            lfu_set.erase(node);
            node.cnt++;
            node.time = time++;
            node.value = value;
            lfu_set.insert(node);
            lfu_hash[key] = node;

        }
    }
};


int main() {
	LFUCache cache(2);
	cache.put(1, 3);
	cache.put(2, 4);
    cout << cache.get(1) << endl;
    cache.put(3, 4);
	cout << cache.get(2) << endl;
	return 0;
}