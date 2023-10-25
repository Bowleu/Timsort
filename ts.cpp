#include "ts.h"

using namespace std;

int getMinRun(int n) {
    int r = 0;
    while (n >= 64) {
        r |= (n & 1);
        n /= 2;
    }
    return n + r;
}

int* merge(vector <int> &arr, int left[2], int right[2]) {
    if (left[0] > right[0]) {
        swap(left[0], right[0]);
        swap(left[1], right[1]);
    }
    int result[2];
    result[0] = left[0];
    result[1] = left[1] + right[1];
    vector <int> temp;
    for (int i = 0; i < left[1]; i++)
        temp.push_back(arr[left[0] + i]);
    int leftIndex = 0;
    int rightIndex = 0;
    while (leftIndex < left[1] and rightIndex < right[1]) {
        if (temp[leftIndex] < arr[right[0] + rightIndex]) {
            arr[result[0] + leftIndex + rightIndex] = temp[leftIndex];
            leftIndex++;
        }
        else {
            arr[result[0] + leftIndex + rightIndex] = arr[right[0] + rightIndex];
            rightIndex++;
        }
    }
    while (leftIndex < left[1]) {
        arr[result[0] + leftIndex + rightIndex] = temp[leftIndex];
        leftIndex++;
    }
    while (rightIndex < right[1]) {
        arr[result[0] + leftIndex + rightIndex] = arr[right[0] + rightIndex];
        rightIndex++;
    }
    return result;
}

vector <int> timsort(vector <int> arr) {
    int n = arr.size();
    int minRun = getMinRun(n);               // 32 <= minRun <= 64

    // Step 1. Separation and sorting Runs.

    int start = 0;
    int step = 2;

    stack <runInfo> runs;

    while (start < n) {

        // Step 1.1; Getting Run.

        if (start + 1 < n) {
            if (arr[start] > arr[start + 1])
                swap(arr[start], arr[start + 1]);
        }
        else
            step = 1;
        while (start + step < n and arr[start + step] >= arr[start + step - 1]) {
            step++;
        }
        while (start + step < n and step < minRun) {
            step++;
        }

        // Step 1.2. Sorting Run.

        for (int i = 2; i < step; i++) {
            int a = arr[start + i];
            int j = i;
            while (j > 0 and arr[start + j - 1] > a) {
                arr[start + j] = arr[start + j - 1];
                j--;
            }
            arr[start + j] = a;
        }
        runs.push({ start, step });
        while (runs.size() > 2) {
            int first[2] = { runs.top()[0], runs.top()[1] };
            runs.pop();
            int second[2] = { runs.top()[0], runs.top()[1] };
            runs.pop();
            int third[2] = { runs.top()[0], runs.top()[1] };
            runs.pop();
            int* result;
            if (third[1] > first[1] + second[1]) {
                if (second[1] > first[1]) {
                    runs.push(third);
                    runs.push(second);
                    runs.push(first);
                    break;
                }
                else {
                    result = merge(arr, first, second);
                    if (result[1] < third[1]) {
                        runs.push(third);
                        runs.push({ result[0], result[1] });
                    }
                    else {
                        runs.push({ result[0], result[1] });
                        runs.push(third);
                    }
                }
            }
            else {
                if (first[1] < third[1]) {
                    result = merge(arr, second, first);
                    if (result[1] < third[1]) {
                        runs.push(third);
                        runs.push({ result[0], result[1] });
                    }
                    else {
                        runs.push({ result[0], result[1] });
                        runs.push(third);
                    }
                }
                else
                {
                    result = merge(arr, second, third);
                    if (result[1] < first[1]) {
                        runs.push(first);
                        runs.push({ result[0], result[1] });
                    }
                    else {
                        runs.push({ result[0], result[1] });
                        runs.push(first);
                    }
                }
            }
        }
        start = start + step;
        step = 2;
    }

    while (runs.size() > 1) {
        int first[2] = { runs.top()[0], runs.top()[1] };
        runs.pop();
        int second[2] = { runs.top()[0], runs.top()[1] };
        runs.pop();
        int* result = merge(arr, first, second);
        runs.push({ result[0], result[1] });
    }
    if (runs.size() > 0)
        runs.pop();
    return arr;
}