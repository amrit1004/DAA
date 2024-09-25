#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
using namespace std;
using namespace std::chrono;

long long simulatedBinarySearch(long long n, long long x) {
    long long l = 1;
    long long r = n;

    while (l <= r) {
        long long m = l + (r - l) / 2;

        if (m == x)
            return m;

        if (m < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

void measureSearchTime(long long n, long long x, const string& caseType, ofstream &outFile, int iterations = 100) {
    auto totalStart = high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        auto start = high_resolution_clock::now();
        long long result = simulatedBinarySearch(n, x);
        auto stop = high_resolution_clock::now();
    }
    
    auto totalStop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(totalStop - totalStart);
    double averageTime = static_cast<double>(duration.count()) / iterations;

    cout << setw(8) << caseType << setw(20) << n << setw(20) << x << setw(20) << averageTime << " µs" << endl;
    outFile << setw(8) << caseType << setw(20) << n << setw(20) << x << setw(20) << averageTime << " µs\n";
}

void runTest(long long n, ofstream &outFile) {
    // Best case (element found in the middle)
    long long x = n / 2; // Searching for the middle element
    measureSearchTime(n, x, "Best", outFile);

    // Average case (element found somewhere in the middle but not exactly at the center)
    x = n / 4; // Searching for an element in the first quarter
    measureSearchTime(n, x, "Average", outFile);

    // Worst case (element not found)
    x = n + 1; // Searching for a non-existing element
    measureSearchTime(n, x, "Worst", outFile);
}

int main() {
    ofstream outFile("simulated_binary_search_results.txt");
    outFile << setw(8) << "Case" << setw(20) << "N" << setw(20) << "Element" << setw(20) << "Time\n";
    outFile << "-----------------------------------------------------------------------------------\n";

    cout << setw(8) << "Case" << setw(20) << "N" << setw(20) << "Element" << setw(20) << "Time\n";
    cout << "-----------------------------------------------------------------------------------\n";

    runTest(100000000LL, outFile);    // Test with n = 100 million
    runTest(1000000000LL, outFile);   // Test with n = 1 billion
    runTest(10000000000LL, outFile);  // Test with n = 10 billion
    runTest(100000000000LL, outFile); // Test with n = 100 billion

    outFile.close();
    cout << "Results saved to simulated_binary_search_results.txt\n";

    return 0;
 
}
