#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
using namespace std;
using namespace std::chrono;

int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}

void measureSearchTime(int arr[], int n, int x, const string& caseType, ofstream &outFile) {
    auto start = high_resolution_clock::now();
    int result = linearSearch(arr, n, x);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << setw(8) << caseType << setw(12) << n << setw(12) << x << setw(20) << duration.count() << " ns" << endl;
    outFile << setw(8) << caseType << setw(12) << n << setw(12) << x << setw(20) << duration.count() << " ns\n";
}

void runTest(int n, ofstream &outFile) {
    int *arr = new int[n];

    // Best case (element found at the beginning)
    for(int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    int x = 1; // Searching for the first element
    measureSearchTime(arr, n, x, "Best", outFile);

    // Average case (element found somewhere in the middle)
    x = n / 2; // Searching for a middle element
    measureSearchTime(arr, n, x, "Average", outFile);

    // Worst case (element not found or at the end)
    x = n; // Searching for the last element
    measureSearchTime(arr, n, x, "Worst", outFile);

    delete[] arr; // Free the allocated memory
}

int main() {
    ofstream outFile("linear_search_results.txt");
    outFile << setw(8) << "Case" << setw(12) << "N" << setw(12) << "Element" << setw(20) << "Time\n";
    outFile << "-------------------------------------------------------------\n";

    cout << setw(8) << "Case" << setw(12) << "N" << setw(12) << "Element" << setw(20) << "Time\n";
    cout << "-------------------------------------------------------------\n";

    runTest(10, outFile);
    runTest(10000, outFile);
    runTest(100000, outFile);
    runTest(1000000, outFile);

    outFile.close();
    cout << "Results saved to linear_search_results.txt\n";

    return 0;
}
