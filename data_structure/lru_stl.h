#include <list>
#include <map>
#include <stack>

using namespace std;

class LRUCache {
   public:
    LRUCache(int capacity) : capacity_(capacity) {}
    int get(int key) {
        if (hash_.find(key) == hash_.end()) return -1;
        update(key);
        return (*hash_[key]).val;
    }
    void put(int key, int value) {
        if (hash_.find(key) == hash_.end())
            insert(key, value);
        else
            update(key, value);
    }

   private:
    struct Node {
        int key;
        int val;
        Node(int k, int v): key(k), val(v) {}  
    };
    map<int, list<Node>::iterator> hash_;
    list<Node> lst_;
    int capacity_;

    void update(int key) {
        auto cur = hash_[key];
        int val = (*cur).val;
        lst_.erase(cur);

        lst_.push_front(Node(key, val));
        hash_[key] = lst_.begin();
    }
    void update(int key, int val) {
        auto cur = hash_[key];
        lst_.erase(cur);

        lst_.push_front(Node(key, val));
        hash_[key] = lst_.begin();
    }
    void insert(int key, int val) {
        if(lst_.size() < capacity_) {
            lst_.push_front(Node(key, val));
            hash_[key] = lst_.begin();
        }
        else {
            lst_.push_front(Node(key, val));
            hash_[key] = lst_.begin();

            int last_key = lst_.back().key;
            hash_.erase(last_key);
            lst_.pop_back();
        }
    }
};