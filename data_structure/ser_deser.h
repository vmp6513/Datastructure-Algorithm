#include <queue>
#include <string>
#include <vector>

using namespace std;

/**
 * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void split(const string& str, vector<string>& arr,
           const string& delimiters = " ") {
    size_t left_pos = str.find_first_not_of(delimiters, 0);
    size_t right_pos = str.find_first_of(delimiters, left_pos);

    while (left_pos != str.npos || right_pos != str.npos) {
        arr.push_back(str.substr(left_pos, right_pos - left_pos));
        left_pos = str.find_first_not_of(delimiters, right_pos);
        right_pos = str.find_first_of(delimiters, left_pos);
    }
}

string serialize(TreeNode* root) {
    string ret;
    if (!root) {
        return ret;
    }
    queue<TreeNode*> q;
    q.push(root);
    ret += to_string(root->val) + ",";
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            if (node->left) {
                q.push(node->left);
                ret += to_string(node->left->val) + ",";
            } else {
                ret += "null,";
            }
            if (node->right) {
                q.push(node->right);
                ret += to_string(node->right->val) + ",";
            } else {
                ret += "null,";
            }
        }
    }
    ret.pop_back(); // remove last comma
    return ret;
}

TreeNode* deserialize(string data) {
    if (data.empty() || data == "null") {
        return NULL;
    }
    vector<string> arr;
    split(data, arr, ",");
    TreeNode* root = new TreeNode(stoi(arr[0]));
    queue<TreeNode*> q;
    q.push(root);
    for (int i = 1; !q.empty() && i < arr.size();) {
        TreeNode* node = q.front();
        q.pop();
        if (arr[i] != "null") {
            node->left = new TreeNode(stoi(arr[i]));
            q.push(node->left);
        }
        i++;
        if (arr[i] != "null") {
            node->right = new TreeNode(stoi(arr[i]));
            q.push(node->right);
        }
        i++;
    }
    return root;
}
