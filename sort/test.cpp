#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <iostream>

#include "bubble_sort.h"
#include "heap_sort.h"
#include "insert_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "select_sort.h"

#define SIZE 80000

int main() {
    srand((unsigned int)time(NULL));
    vector<int> arr(SIZE);
    for (int& a : arr) {
        a = rand();
    }
    clock_t start;
    double duration;
    vector<int> correct_answer(arr);
    start = clock();
    sort(correct_answer.begin(), correct_answer.end());
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << "STL sort cost time = " << duration << "s" << endl;
    //-------------------------------------------
    vector<int> test(arr);
    cout << "*****bubble sort*****" << endl;
    start = clock();
    bubble_sort(test);
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    if (test == correct_answer) {
        cout << "OK, cost time = " << duration << "s" << endl;
    } else {
        cout << "FAIL, cost time = " << duration << "s" << endl;
    }
    cout << endl << endl;
    test = arr;
    //-------------------------------------------
    cout << "*****heap sort*****" << endl;
    start = clock();
    heap_sort(test);
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    if (test == correct_answer) {
        cout << "OK, cost time = " << duration << "s" << endl;
    } else {
        cout << "FAIL, cost time = " << duration << "s" << endl;
    }
    cout << endl << endl;
    test = arr;
    //-------------------------------------------
    cout << "*****insert sort*****" << endl;
    start = clock();
    insert_sort(test);
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    if (test == correct_answer) {
        cout << "OK, cost time = " << duration << "s" << endl;
    } else {
        cout << "FAIL, cost time = " << duration << "s" << endl;
    }
    cout << endl << endl;
    test = arr;
    //-------------------------------------------
    cout << "*****merge sort*****" << endl;
    start = clock();
    merge_sort(test);
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    if (test == correct_answer) {
        cout << "OK, cost time = " << duration << "s" << endl;
    } else {
        cout << "FAIL, cost time = " << duration << "s" << endl;
    }
    cout << endl << endl;
    test = arr;
    //-------------------------------------------
    cout << "*****quick sort*****" << endl;
    start = clock();
    quick_sort(test);
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    if (test == correct_answer) {
        cout << "OK, cost time = " << duration << "s" << endl;
    } else {
        cout << "FAIL, cost time = " << duration << "s" << endl;
    }
    cout << endl << endl;
    test = arr;
    //-------------------------------------------
    cout << "*****select sort*****" << endl;
    start = clock();
    select_sort(test);
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    if (test == correct_answer) {
        cout << "OK, cost time = " << duration << "s" << endl;
    } else {
        cout << "FAIL, cost time = " << duration << "s" << endl;
    }
    cout << endl << endl;
    test = arr;
}