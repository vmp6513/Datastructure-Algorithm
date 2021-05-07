#include <list>
#include <map>

class LRUCache {
   public:
    LRUCache(int capacity)
        : capacity_(capacity),
          size_(0),
          head_(new Node(-1, -1)),
          tail_(new Node(-1, -1)) {
        head_->next = tail_;
        tail_->prev = head_;
    }

    int get(int key) {
        if (hash_.find(key) == hash_.end()) return -1;
        update(key);
        return hash_[key]->val;
    }

    void put(int key, int value) {
        if (hash_.find(key) != hash_.end())
            update(key, value);
        else
            insert(key, value);
    }

   private:
    struct Node {
        int key;
        int val;
        Node* next;
        Node* prev;
        Node(int k, int v) : key(k), val(v), next(NULL), prev(NULL) {}
        ~Node() {
            delete next;
            delete prev;
        }
    };

    Node* head_;
    Node* tail_;
    std::map<int, Node*> hash_;
    int capacity_;
    int size_;

    void update(int key) {
        if (size_ == 1) return;
        Node* cur = hash_[key];

        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        cur->next = head_->next;
        cur->prev = head_;
        head_->next->prev = cur;
        head_->next = cur;
    }
    void update(int key, int value) {
        hash_[key]->val = value;
        update(key);
    }
    void insert(int key, int value) {
        if (hash_.find(key) != hash_.end()) {
            update(key, value);
        } else {
            if (size_ < capacity_) {
                size_++;
                Node* cur = new Node(key, value);
                hash_[key] = cur;

                cur->next = head_->next;
                cur->prev = head_;
                head_->next->prev = cur;
                head_->next = cur;
            } else {
                Node* last = tail_->prev;
                int tmp = last->key;
                hash_.erase(tmp);
                last->key = key;
                last->val = value;
                hash_[key] = last;
                update(key);
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */