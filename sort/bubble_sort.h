#include <vector>
using namespace std;

// @冒泡排序
// 时间复杂度：O(n^2), 空间复杂度：O(1), 最坏情况：O(n^2)
// 稳定

void bubble_sort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    for (int i = arr.size() - 1; i >= 0; i--) {
        bool flag = false;
        for (int j = 0; j < i; j++) {
            if (arr[j + 1] < arr[j]) {
                swap(arr[j + 1], arr[j]);
                flag = true;
            }
        }
        if (!flag) {
            return;
        }
    }
}