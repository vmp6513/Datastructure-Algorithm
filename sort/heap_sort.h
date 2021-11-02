#include <vector>
using namespace std;

// @堆排序，这里是大根堆
// 时间复杂度：O(nlogn)，空间复杂度：O(1)，不稳定
void _make_heap(vector<int>& arr, int pos, int size);

void heap_sort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    for (int i = arr.size() / 2 - 1; i >= 0; i--) {
        _make_heap(arr, i, arr.size());
    }

    for (int i = arr.size() - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        _make_heap(arr, 0, i);
    }
}

void _make_heap(vector<int>& arr, int pos, int size) {
    int child;
    int tmp = arr[pos];
    for (; pos * 2 + 1 < size; pos = child) {
        child = pos * 2 + 1;
        if (child + 1 < size && arr[child + 1] > arr[child]) {
            child += 1;
        }

        if (arr[child] > tmp) {
            arr[pos] = arr[child];
        } else {
            break;
        }
    }

    arr[pos] = tmp;
}