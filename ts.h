#include "Containers/vector.h"
#include "Containers/stack.h"
#include "graphicsFunctions.h"

using namespace std;

struct runInfo{
    int start;
    int step;
    runInfo() {
        start = 0;
        step = 0;
    }
    runInfo(int start, int step) {
        this->start = start;
        this->step = step;
    }
    runInfo(int arr[2]) {
        start = arr[0];
        step = arr[1];
    }
    int operator [] (int index) {
        if (index == 0)
            return start;
        return step;
    }
};

using namespace std;

int getMinRun(int n) {
    int r = 0;
    while (n >= 64) {
        r |= (n & 1);
        n /= 2;
    }
    return n + r;
}

int binSearch(vector <int> arr, int start, int end, int value) {
    end -= 1;
    int m = (start + end) / 2;
    while (start + 1 < end) {
        if (value < arr[m])
            end = m;
        else
            start = m;
        m = (end + start) / 2;
    }
    return start;
}

vector <int> merge(vector <int>& arr, int left[2], int right[2]) {
    if (left[0] > right[0]) {
        swap(left[0], right[0]);
        swap(left[1], right[1]);
    }
    vector <int> result;
    result.push(left[0]);
    result.push(left[1] + right[1]);
    vector <int> temp;
    for (int i = 0; i < left[1]; i++)
        temp.push(arr[left[0] + i]);
    int leftIndex = 0;
    int rightIndex = 0;
    int betterCounter = 1;
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
    int n = arr.getLength();
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
        while (runs.getLength() > 2) {
            int first[2] = { (runs.peek())[0], (runs.peek())[1] };
            runs.pop();
            int second[2] = { (runs.peek())[0], (runs.peek())[1] };
            runs.pop();
            int third[2] = { (runs.peek())[0], (runs.peek())[1] };
            runs.pop();
            vector <int> result;
            if (third[1] > first[1] + second[1]) {
                if (second[1] > first[1]) {
                    runs.push(third);
                    runs.push(second);
                    runs.push(first);
                    break;
                }
                else {
                    result = merge(arr, first, second);
                    if (result[0] < third[0]) {
                        runs.push({ result[0], result[1] });
                        runs.push(third);
                    }
                    else {
                        runs.push(third);
                        runs.push({ result[0], result[1] });
                    }
                }
            }
            else {
                if (first[1] < third[1]) {
                    result = merge(arr, second, first);
                    if (result[0] < third[0]) {
                        runs.push({ result[0], result[1] });
                        runs.push(third);
                    }
                    else {
                        runs.push(third);
                        runs.push({ result[0], result[1] });
                    }
                }
                else
                {
                    result = merge(arr, second, third);
                    if (result[0] < first[0]) {
                        runs.push({ result[0], result[1] });
                        runs.push(first);
                    }
                    else {
                        runs.push(first);
                        runs.push({ result[0], result[1] });
                    }
                }
            }
        }
        start = start + step;
        step = 2;
    }

    while (runs.getLength() > 1) {
        int first[2] = { (runs.peek())[0], (runs.peek())[1] };
        runs.pop();
        int second[2] = { (runs.peek())[0], (runs.peek())[1] };
        runs.pop();
        vector <int> result = merge(arr, first, second);
        runs.push({ result[0], result[1] });
    }
    if (runs.getLength() > 0)
        runs.pop();
    return arr;
}

/*

        Функции ниже используются только для графического отображения сортировки timsort.
        ********************************************************************************
        Отличие от функций выше - наличие графического вывода.

*/

int maximum(vector <int> arr) {
    if (arr.getLength() == 0)
        return -1;
    int mx = arr[0];
    for (int i = 1; i < arr.getLength(); i++) {
        if (arr[i] > mx)
            mx = arr[i];
    }
    return mx;
}

int minimum(vector <int> arr) {
    if (arr.getLength() == 0)
        return -1;
    int mn = arr[0];
    for (int i = 1; i < arr.getLength(); i++) {
        if (arr[i] < mn)
            mn = arr[i];
    }
    return mn;
}

int mx, mn;

vector <int> mergeShow(vector <int>& arr, int left[2], int right[2]) {
    if (left[0] > right[0]) {
        swap(left[0], right[0]);
        swap(left[1], right[1]);
    }
    vector <int> result;
    result.push(left[0]);
    result.push(left[1] + right[1]);
    vector <int> temp;
    for (int i = 0; i < left[1]; i++)
        temp.push(arr[left[0] + i]);
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
        drawArr(arr, mx, mn);
    }
    while (leftIndex < left[1]) {
        arr[result[0] + leftIndex + rightIndex] = temp[leftIndex];
        leftIndex++;
        drawArr(arr, mx, mn);
    }
    while (rightIndex < right[1]) {
        arr[result[0] + leftIndex + rightIndex] = arr[right[0] + rightIndex];
        rightIndex++;
        drawArr(arr, mx, mn);
    }
    return result;
}

vector <int> timsortShow(vector <int> arr) {
    mx = maximum(arr);
    mn = minimum(arr);
    int n = arr.getLength();
    int minRun = getMinRun(n);               // 32 <= minRun <= 64

    // Step 1. Separation and sorting Runs.

    int start = 0;
    int step = 2;

    stack <runInfo> runs;

    while (start < n) {

        // Step 1.1; Getting Run.

        if (start + 1 < n) {
            if (arr[start] > arr[start + 1])
            {
                swap(arr[start], arr[start + 1]);
                drawArr(arr, mx, mn);
            }
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
                drawArr(arr, mx, mn);
            }
            arr[start + j] = a;
            drawArr(arr, mx, mn);
        }
        runs.push({ start, step });
        vector <int> result;
        while (runs.getLength() > 2) {
            int first[2] = { (runs.peek())[0], (runs.peek())[1] };
            runs.pop();
            int second[2] = { (runs.peek())[0], (runs.peek())[1] };
            runs.pop();
            int third[2] = { (runs.peek())[0], (runs.peek())[1] };
            runs.pop();
            if (third[1] > first[1] + second[1]) {
                if (second[1] > first[1]) {
                    runs.push(third);
                    runs.push(second);
                    runs.push(first);
                    break;
                }
                else {
                    result = mergeShow(arr, first, second);
                    if (result[0] < third[0]) {
                        runs.push({ result[0], result[1] });
                        runs.push(third);
                    }
                    else {
                        runs.push(third);
                        runs.push({ result[0], result[1] });
                    }
                }
            }
            else {
                if (first[1] < third[1]) {
                    result = mergeShow(arr, second, first);
                    if (result[0] < third[0]) {
                        runs.push({ result[0], result[1] });
                        runs.push(third);
                    }
                    else {
                        runs.push(third);
                        runs.push({ result[0], result[1] });
                    }
                }
                else
                {
                    result = mergeShow(arr, second, third);
                    if (result[0] < first[0]) {
                        runs.push({ result[0], result[1] });
                        runs.push(first);
                    }
                    else {
                        runs.push(first);
                        runs.push({ result[0], result[1] });
                    }
                }
            }
        }
        if (runs.getLength() == 2) {
            int first[2] = { runs.peek()[0], runs.peek()[1] };
            runs.pop();
            int second[2] = { runs.peek()[0], runs.peek()[1] };
            runs.pop();
            if (second[1] > first[1]) {
                runs.push(second);
                runs.push(first);
            }
            else {
                result = mergeShow(arr, second, first);
                runs.push({ result[0], result[1] });
                drawArr(arr, mx, mn);
            }
        }
        start = start + step;
        step = 2;
    }

    while (runs.getLength() > 1) {
        int first[2] = { runs.peek()[0], runs.peek()[1] };
        runs.pop();
        int second[2] = { runs.peek()[0], runs.peek()[1] };
        runs.pop();
        vector <int> result = mergeShow(arr, first, second);
        runs.push({ result[0], result[1] });
        drawArr(arr, mx, mn);
    }
    if (runs.getLength() > 0)
        runs.pop();
    return arr;
}