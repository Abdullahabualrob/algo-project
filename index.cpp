#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;
using namespace chrono;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftPart(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftPart.size() && j < rightPart.size()) {
        if (leftPart[i] < rightPart[j]) {
            arr[k++] = leftPart[i++];
        } else {
            arr[k++] = rightPart[j++];
        }
    }

    while (i < leftPart.size()) arr[k++] = leftPart[i++];
    while (j < rightPart.size()) arr[k++] = rightPart[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int idx = partition(arr, low, high);
        quickSort(arr, low, idx - 1);
        quickSort(arr, idx + 1, high);
    }
}

vector<int> generateArray(int size, string order) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);

    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }

    if (order == "sorted") {
        sort(arr.begin(), arr.end());
    } else if (order == "reversed") {
        sort(arr.begin(), arr.end(), greater<int>());
    } else if (order == "partial") {
        sort(arr.begin(), arr.begin() + size / 2);
    }

    return arr;
}

template <typename SortFunc>
double measureTime(SortFunc sortFunction, vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

void mergeCall(vector<int> arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

void quickCall(vector<int> arr) {
    quickSort(arr, 0, arr.size() - 1);
}

int main() {
    vector<int> sizes = {100, 1000, 10000};
    vector<string> orders = {"random", "partial", "reversed"};

    cout << "\n==== Sorting Algorithm Performance (ms) ====\n\n";

    for (auto order : orders) {
        cout << "-- Order: " << order << " --\n";
        cout << setw(10) << "Size" 
             << setw(16) << "Bubble Sort"
             << setw(16) << "Merge Sort"
             << setw(16) << "Quick Sort" << endl;

        for (int size : sizes) {
            double bubbleTime = 0, mergeTime = 0, quickTime = 0;

            for (int i = 0; i < 5; i++) {
                vector<int> baseArr = generateArray(size, order);
                bubbleTime += measureTime(bubbleSort, baseArr);
                mergeTime += measureTime(mergeCall, baseArr);
                quickTime += measureTime(quickCall, baseArr);
            }

            cout << setw(10) << size
                 << setw(16) << fixed << setprecision(2) << bubbleTime / 5
                 << setw(16) << mergeTime / 5
                 << setw(16) << quickTime / 5 << endl;
        }
        cout << endl;
    }

    return 0;
}
