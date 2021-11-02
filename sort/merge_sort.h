#include <vector>
using namespace std;

// 归并排序
// @2-路归并排序
// 时间复杂度：O(n*logn), 空间复杂度：O(n), 最坏情况：O(n*logn)
// 稳定
void _merge_sort(vector<int>& arr, int left, int right);
void _merge(vector<int>& arr, int left, int mid, int right);

void merge_sort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }
    _merge_sort(arr, 0, arr.size() - 1);
}

void _merge_sort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = (left + right) >> 1;
    _merge_sort(arr, left, mid);
    _merge_sort(arr, mid + 1, right);

    _merge(arr, left, mid, right);
}

void _merge(vector<int>& arr, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    vector<int> tmp;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            tmp.push_back(arr[i++]);
        } else {
            tmp.push_back(arr[j++]);
        }
    }

    while (i <= mid) {
        tmp.push_back(arr[i++]);
    }
    while (j <= right) {
        tmp.push_back(arr[j++]);
    }

    for (int i = 0; i < tmp.size(); i++) {
        arr[i + left] = tmp[i];
    }
}