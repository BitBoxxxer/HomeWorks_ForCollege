#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

// 1
template <typename T>
T average(const vector<T>& arr) {
    if (arr.empty()) return 0;
    T sum = 0;
    for (const T& val : arr) {
        sum += val;
    }
    return sum / arr.size();
}

// 2
template <typename T>
T solveLinear(T a, T b) {
    if (a == 0) return 0;
    return -b / a;
}

// 3
template <typename T>
T findMax(const vector<T>& arr) {
    if (arr.empty()) return 0;
    T maxVal = arr[0];
    for (const T& val : arr) {
        if (val > maxVal) maxVal = val;
    }
    return maxVal;
}

template <typename T>
T findMax(const vector<vector<T>>& matrix) {
    if (matrix.empty()) return 0;
    T maxVal = matrix[0][0];
    for (const auto& row : matrix) {
        for (const T& val : row) {
            if (val > maxVal) maxVal = val;
        }
    }
    return maxVal;
}

template <typename T>
T findMax(const vector<vector<vector<T>>>& cube) {
    if (cube.empty()) return 0;
    T maxVal = cube[0][0][0];
    for (const auto& slice : cube) {
        for (const auto& row : slice) {
            for (const T& val : row) {
                if (val > maxVal) maxVal = val;
            }
        }
    }
    return maxVal;
}

// 4
int findMax(int a, int b) {
    return (a > b) ? a : b;
}

int findMax(int a, int b, int c) {
    int maxAB = (a > b) ? a : b;
    return (maxAB > c) ? maxAB : c;
}

int main() {
    // 1
    vector<double> nums = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    cout << "Average: " << average(nums) << endl;

    // 2
    double linearRoot = solveLinear(2.0, 4.0);
    cout << "Linear Root: " << linearRoot << endl;

    // 3
    vector<int> arr1 = { 1, 5, 2, 8, 3 };
    cout << "Max 1D: " << findMax(arr1) << endl;

    vector<vector<int>> arr2 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    cout << "Max 2D: " << findMax(arr2) << endl;

    vector<vector<vector<int>>> arr3 = {
        {{1,2},{3,4}},
        {{5,6},{7,8}},
         {{9,10},{11,12}},
    };

    cout << "Max 3D: " << findMax(arr3) << endl;

    // 4
    cout << "Max 2 ints: " << findMax(5, 10) << endl;
    cout << "Max 3 ints: " << findMax(5, 10, 2) << endl;
}