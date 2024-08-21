#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
using namespace std;
using namespace std::chrono;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void measureSortTime(int arr[], int n, const string& caseType, ofstream &outFile) {
    auto total_duration = 0;
    int repetitions = 10; 

    for (int i = 0; i < repetitions; i++) {
        int* tempArr = new int[n];
        copy(arr, arr + n, tempArr);

        auto start = high_resolution_clock::now();
        mergeSort(tempArr, 0, n - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start).count();
        total_duration += duration;

        delete[] tempArr;
    }

    long long average_duration = total_duration / repetitions;

    cout << setw(8) << caseType << setw(12) << n << setw(20) << average_duration << " ns" << endl;
    outFile << setw(8) << caseType << setw(12) << n << setw(20) << average_duration << " ns\n";
}

void runTest(int n, ofstream &outFile) {
    int* arr = new int[n];

    // Best case (already sorted)
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    measureSortTime(arr, n, "Best", outFile);

    // Average case (random order)
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    measureSortTime(arr, n, "Average", outFile);

    // Worst case (reverse sorted)
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    measureSortTime(arr, n, "Worst", outFile);

    delete[] arr; // Free the allocated memory
}

int main() {
    ofstream outFile("merge_sort_results.txt");
    outFile << setw(8) << "Case" << setw(12) << "N" << setw(20) << "Time\n";
    outFile << "---------------------------------------------\n";

    cout << setw(8) << "Case" << setw(12) << "N" << setw(20) << "Time\n";
    cout << "---------------------------------------------\n";

    runTest(10, outFile);
    runTest(100, outFile);
    runTest(1000, outFile);
    runTest(10000, outFile);
    runTest(100000, outFile);
    runTest(1000000, outFile);

    outFile.close();
    cout << "Results saved to merge_sort_results.txt\n";

    return 0;
}
