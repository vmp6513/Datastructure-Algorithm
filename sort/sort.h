#include <stdio.h>

#include <vector>

using namespace std;

// @插入排序
// 时间复杂度：O(n^2), 空间复杂度：O(1), 最坏情况：O(n^2)
// 稳定
// 适用于n很小且局部有序

void insertion_sort(vector<int>& arr) {
    printf("insertion sort:\n");
    if (arr.empty()) return;

    int i, j;
    for (i = 1; i < arr.size(); i++) {
        int tmp = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > tmp; j--) arr[j + 1] = arr[j];
        arr[j + 1] = tmp;
    }
}

// @希尔排序
// 时间复杂度：O(n^1.3), 空间复杂度：O(1), 最坏情况：O(n^1.3)
// 不稳定
// 适用于记录数量较大
void shell_sort(vector<int>& vec) {
    printf("shell sort:\n");
    if (vec.empty()) return;

    int gap, i, j;
    size_t size = vec.size();
    for (gap = size >> 1; gap >= 1; gap = gap >> 1) {
        for (i = gap; i < size; i++) {
            int tmp = vec[i];
            for (j = i - gap; j >= 0 && vec[j] > tmp; j -= gap)
                vec[j + gap] = vec[j];
            vec[j + gap] = tmp;
        }
    }
}

// 交换排序

// @冒泡排序
// 时间复杂度：O(n^2), 空间复杂度：O(1), 最坏情况：O(n^2)
// 稳定

void bubble_sort(vector<int>& arr) {
    printf("bubble sort:\n");
    if (arr.empty()) return;

    bool flag = true;
    for (int i = arr.size() - 1; i > 0; i--) {
        flag = false;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
            flag = false;
        }
    }
}

// @快速排序
// 时间复杂度：O(n*logn), 空间复杂度：O(logn), 最坏情况：O(n^2)
// 不稳定
// 遇到的问题：1.单次快排时，每次主循环，如果以low为中心，必须从大往小排
//              原因是，如果从小往大排，第一个low位置必被跳过，相当于少了一个位置没填
//            2.中心的选择，为什么要选中心，如果选的不好，单次快排会退化成冒泡排序，时间复杂度
//              变成O(n^2)(理解)，一般采用三者取中法
//            3.每次快排，至少有一个数找到最终位置
int _once_quick_sort(vector<int>& vec, int low, int high);
void _quick_sort(vector<int>& vec, int low, int high);
void quick_sort(vector<int>& vec) {
    printf("quick sort:\n");
    if (vec.empty()) return;

    size_t size = vec.size();
    _quick_sort(vec, 0, size - 1);
}

int _once_quick_sort(vector<int>& vec, int low, int high) {
    int pivot = vec[low];
    while (low < high) {
        while (low < high && vec[high] >= pivot) high--;
        if (low < high) vec[low++] = vec[high];
        while (low < high && vec[low] <= pivot) low++;
        if (low < high) vec[high--] = vec[low];
    }

    vec[low] = pivot;
    return low;
}

void _quick_sort(vector<int>& vec, int low, int high) {
    if (low >= high) return;
    int pivot = _once_quick_sort(vec, low, high);
    _quick_sort(vec, low, pivot - 1);
    _quick_sort(vec, pivot + 1, high);
}

// 选择排序

// @选择排序
// 时间复杂度：O(n^2), 空间复杂度：O(1), 最坏情况：O(n^2)
// 不稳定

void select_sort(vector<int>& arr) {
    if (arr.empty()) return;
    printf("select sort:\n");

    for (int i = 0; i < arr.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[min]) min = j;
        swap(arr[i], arr[min]);
    }
}

// 归并排序
// @2-路归并排序
// 时间复杂度：O(n*logn), 空间复杂度：O(n), 最坏情况：O(n*logn)
// 稳定

void _merge(vector<int>& vec, int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = 0;
    vector<int> tmp(high - low + 1);
    while (i <= mid && j <= high) {
        if (vec[i] <= vec[j])
            tmp[k++] = vec[i++];
        else
            tmp[k++] = vec[j++];
    }
    while (i <= mid) tmp[k++] = vec[i++];
    while (j <= high) tmp[k++] = vec[j++];
    for (int t = 0; t < tmp.size(); t++) {
        vec[low + t] = tmp[t];
    }
}

void _merge_sort(vector<int>& vec, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) >> 1;
    _merge_sort(vec, low, mid);
    _merge_sort(vec, mid + 1, high);
    _merge(vec, low, mid, high);
}

void merge_sort(vector<int>& vec) {
    if (vec.empty()) return;
    printf("merge sort:\n");

    _merge_sort(vec, 0, vec.size() - 1);
}

// @堆排序，这里是大根堆
// 时间复杂度：O(nlogn)，空间复杂度：O(1)，不稳定

void sift_down(vector<int>& arr, int pos, int size) {
    int child;
    int tmp = arr[pos];
    for (; pos * 2 + 1 < size; pos = child) {
        child = pos * 2 + 1;
        if (child != size - 1 && arr[child + 1] > arr[child]) child++;
        if (arr[child] > tmp)
            arr[pos] = arr[child];
        else
            break;
    }
    arr[pos] = tmp;
}

void heap_sort(vector<int>& arr) {
    if (arr.empty()) return;
    printf("heap sort:\n");

    size_t size = arr.size();
    for (int i = size / 2 - 1; i >= 0; i--) sift_down(arr, i, size);

    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        sift_down(arr, 0, i);
    }
}

// 基于堆排序的TOP K问题

void topk_heap(vector<int>& arr, int k, vector<int>& res) {
    for (int i = 0; i < k; i++) res.push_back(arr[i]);

    for (int i = k / 2 - 1; i >= 0; i--) {
        // 这里是建立大根堆
        sift_down(res, i, k);
    }

    for (int i = k; i < arr.size(); i++) {
        if (arr[i] < res[0]) {
            res[0] = arr[i];
            sift_down(res, 0, k);
        }
    }
}