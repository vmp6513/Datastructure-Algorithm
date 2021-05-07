// From leetcode_208

#include <string>
#include <vector>

class Trie {
   public:
    // 仅支持小写字母
    Trie() : children(26), isEnd(false) {}

    void insert(const std::string& word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) node->children[ch] = new Trie();
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool search(const std::string& word) const {
        const Trie* node = searchPrefix(word);
        return node != nullptr && node->isEnd;
    }
    bool startsWith(const std::string& prefix) const {
        const Trie* node = searchPrefix(prefix);
        return node != nullptr;
    }

   private:
    std::vector<Trie*> children;
    bool isEnd;

    const Trie* searchPrefix(const std::string& prefix) const {
        const Trie* node = this;
        for (char ch : prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) return nullptr;
            node = node->children[ch];
        }
        return node;  
    }
};