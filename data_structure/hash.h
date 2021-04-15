

#include <bits/stdc++.h>
using namespace std;

size_t default_hash(int key, size_t capacity) { return key % capacity; }

// 开散列表哈希
template <typename key_type, typename value_type>
class open_hash {
    typedef key_type KEY;
    typedef value_type VALUE;

   private:
    struct Node {
        /* data */
        KEY key;
        VALUE val;
        Node* next;
        Node(KEY k = -1, VALUE v = -1, Node* n = NULL)
            : key(k), val(v), next(n) {}
    };
    Node** data;
    size_t size;
    size_t capacity;
    size_t (*hash_func)(int k, size_t cap);

   public:
    open_hash(size_t cap = 59,
              size_t (*hash)(int k, size_t cap) = default_hash);
};

template <typename key_type, typename value_type>
open_hash<key_type, value_type>::open_hash(size_t cap,
                                           size_t (*hash)(int k, size_t cap))
    : size(0), capacity(cap), hash_func(hash) {
    data = new Node*[capacity];
    for (int i = 0; i < capacity; i++) data[i] = new Node;
}
