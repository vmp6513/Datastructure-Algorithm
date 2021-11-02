#include <vector>
using namespace std;

// @插入排序
// 时间复杂度：O(n^2), 空间复杂度：O(1), 最坏情况：O(n^2)
// 稳定
// 适用于n很小且局部有序

void insert_sort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    for (int i = 0; i < arr.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}