#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int value;

    // Constructor to initialize the item
    Item(int w, int v) : weight(w), value(v) {}
};

// Function to compare two items based on value-to-weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Function to calculate maximum profit for fractional knapsack
double fractionalKnapsack(int W, vector<Item> &items) {
    // Sort items based on value-to-weight ratio
    sort(items.begin(), items.end(), compare);

    double maxValue = 0.0;  // Total value in knapsack
    int currentWeight = 0;  // Current weight in knapsack

    // Loop through each item
    for (Item &item : items) {
        if (currentWeight + item.weight <= W) {
            // If the item can be fully included
            currentWeight += item.weight;
            maxValue += item.value;
        } else {
            // If only a fraction of the item can be included
            int remainingWeight = W - currentWeight;
            maxValue += item.value * ((double)remainingWeight / item.weight);
            break;
        }
    }

    return maxValue;
}

int main() {
    int W = 50;  // Knapsack capacity

    // List of items (weight, value)
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};

    // Call the function and print the result
    cout << "Maximum value in knapsack = " << fractionalKnapsack(W, items) << endl;

    return 0;
}
