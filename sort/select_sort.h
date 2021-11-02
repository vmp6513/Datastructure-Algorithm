#include <vector>
using namespace std;

// @选择排序
// 时间复杂度：O(n^2), 空间复杂度：O(1), 最坏情况：O(n^2)
// 不稳定

void select_sort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        int j = i;
        int tmp = arr[i + 1];
        for (; j >= 0 && arr[j] > tmp; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = tmp;
    }
}