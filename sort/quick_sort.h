#include <vector>
using namespace std;

// @快速排序
// 时间复杂度：O(n*logn), 空间复杂度：O(logn), 最坏情况：O(n^2)
// 不稳定
// 遇到的问题：1.单次快排时，每次主循环，如果以low为中心，必须从大往小排
//              原因是，如果从小往大排，第一个low位置必被跳过，相当于少了一个位置没填
//            2.中心的选择，为什么要选中心，如果选的不好，单次快排会退化成冒泡排序，时间复杂度
//              变成O(n^2)(理解)，一般采用三者取中法
//            3.每次快排，至少有一个数找到最终位置
void _quick_sort(vector<int>& arr, int left, int right);
int _partition(vector<int>& arr, int left, int right);

void quick_sort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    _quick_sort(arr, 0, arr.size() - 1);
}

void _quick_sort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = _partition(arr, left, right);
    _quick_sort(arr, left, pivot - 1);
    _quick_sort(arr, pivot + 1, right);
}

int _partition(vector<int>& arr, int left, int right) {
    int tmp = arr[left];

    while (left < right) {
        while (left < right && arr[right] > tmp) {
            right--;
        }

        if (left < right) {
            arr[left] = arr[right];
            left++;
        }

        while (left < right && arr[left] < tmp) {
            left++;
        }

        if (left < right) {
            arr[right] = arr[left];
            right--;
        }
    }

    arr[left] = tmp;
    return left;
}