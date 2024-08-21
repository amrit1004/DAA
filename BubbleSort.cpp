#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void measureSortTime(int arr[], int n, const string& caseType) {
    auto start = high_resolution_clock::now();
    bubbleSort(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << caseType << " case time taken by bubbleSort: "
         << duration.count() << " microseconds" << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[n];

    // Best case (already sorted)
    for(int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    measureSortTime(arr, n, "Best");

    // Average case (random order)
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    measureSortTime(arr, n, "Average");

    // Worst case (reverse sorted)
    for(int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    measureSortTime(arr, n, "Worst");

    return 0;
}
