/*
    中缀表达式求值
*/
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// 计算器：包含+ - * / ( ) 整数

void calc(stack<int>& nums, stack<char>& ops) {
    int right = nums.top();
    nums.pop();
    int left = nums.top();
    nums.pop();
    char op = ops.top();
    ops.pop();
    int ans = 0;
    if ('+' == op) {
        ans = left + right;
    } else if ('-' == op) {
        ans = left - right;
    } else if ('*' == op) {
        ans = left * right;
    } else if ('/' == op) {
        ans = left / right;
    }
    nums.push(ans);
}
int calculate(const string& s) {
    stack<int> nums;
    stack<char> ops;
    nums.push(0);  // 防止第一个是负数

    unordered_map<char, int> priority;
    priority['-'] = 1;
    priority['+'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;
    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];
        if (ch == '(') {
            ops.push('(');
        } else if (ch == ')') {
            while (!ops.empty()) {
                if (ops.top() != '(') {
                    calc(nums, ops);
                } else {
                    ops.pop();
                    break;
                }
            }
        } else if (ch <= '9' && ch >= '0') {
            int num = 0;
            int j = i;
            while (j < s.size() && s[j] <= '9' && s[j] >= '0') {
                num = num * 10 + s[j++] - '0';
            }
            i = j - 1;
            nums.push(num);
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // 注意两个符号连在一起的情况 '(+'  '(-'，加一个0
            if (i > 0 &&
                (s[i - 1] == '(' || s[i - 1] == '-' || s[i - 1] == '+')) {
                nums.push(0);
            }
            while (!ops.empty() && ops.top() != '(') {
                char prev = ops.top();
                if (priority[prev] >= priority[ch]) {
                    calc(nums, ops);
                } else {
                    break;
                }
            }
            ops.push(ch);
        } else {
            continue;
        }
    }
    while (!ops.empty()) {
        calc(nums, ops);
    }
    return nums.top();
}

// 版本2：中缀表达式转后缀表达式
vector<string> mid2post(const string& s) {
    unordered_map<char, int> priority;
    priority['-'] = 1;
    priority['+'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;
    vector<string> ret;
    stack<char> ops;
    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];
        if (ch == '(') {
            ops.push(ch);
        } else if (ch == ')') {
            while (!ops.empty()) {
                if (ops.top() != '(') {
                    ret.push_back(string(1, ops.top()));
                    ops.pop();
                } else {
                    ops.pop();
                    break;
                }
            }
        } else if (ch <= '9' && ch >= '0') {
            int num = 0;
            int j = i;
            while (j < s.size() && s[j] <= '9' && s[j] >= '0') {
                num = num * 10 + s[j++] - '0';
            }
            i = j - 1;
            ret.push_back(to_string(num));
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!ops.empty()) {
                char prev = ops.top();
                if (prev != '(' && priority[prev] >= priority[ch]) {
                    ret.push_back(string(1, ops.top()));
                    ops.pop();
                } else {
                    break;
                }
            }
            ops.push(ch);
        }
    }
    while (!ops.empty()) {
        ret.push_back(string(1, ops.top()));
        ops.pop();
    }
    return ret;
}
int compute(int left, int right, char opr) {
    if (opr == '+') {
        return left + right;
    } else if (opr == '-') {
        return left - right;
    } else if (opr == '*') {
        return left * right;
    } else if (opr == '/') {
        return left / right;
    }
    return 0;
}

int evalRPN(vector<string> rpn) {
    stack<int> nums;
    for (int i = 0; i < rpn.size(); i++) {
        if (rpn[i].size() == 1 && (rpn[i][0] == '+' || rpn[i][0] == '-' ||
                                   rpn[i][0] == '*' || rpn[i][0] == '/')) {
            int left, right;
            right = nums.top();
            nums.pop();
            left = nums.top();
            nums.pop();
            nums.push(compute(left, right, rpn[i][0]));
        } else {
            nums.push(stoi(rpn[i]));
        }
    }
    return nums.top();
}

int main(int argc, char** argv) {
    string str = "12+2*9+(8*7+1)*9";
    cout << calculate(str) << endl;
    cout << evalRPN(mid2post(str)) << endl;
    return 0;
}
