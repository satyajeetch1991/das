#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Structure to hold the value and weight of items along with their index
struct Item {
    int value;
    int weight;
    double ratio;
};
// Comparison function to sort items based on their value-to-weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio; // Sort in descending order of ratio
}
double calculateKnapsackValue(vector<Item>& items, int capacity) {
    double finalVal = 0.0;
    for (const auto& item : items) {
        if (capacity >= item.weight) {
            // Include full item
            capacity -= item.weight;
            finalVal += item.value;
        } else {
            // Include fractional part
            finalVal += (item.ratio * capacity);
            break; // Knapsack is full
        }
    }
    return finalVal;
}
int main() {
    cout << "Enter the number of items: ";
    int n;
    cin >> n;
    vector<Item> items(n);
    cout << "Enter the value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Value of item " << (i + 1) << ": ";
        cin >> items[i].value;
        cout << "Weight of item " << (i + 1) << ": ";
        cin >> items[i].weight;
        items[i].ratio = static_cast<double>(items[i].value) / items[i].weight; // Calculate ratio
    }
    cout << "Enter the knapsack capacity: ";
    int capacity;
    cin >> capacity;
    // Sort items based on value-to-weight ratio
    sort(items.begin(), items.end(), compare);
    double finalVal = calculateKnapsackValue(items, capacity);
    cout << "Final Value: " << finalVal << endl;
    return 0;
}
// Enter the number of items: 3
// Enter the value and weight of each item:
// Value of item 1: 60
// Weight of item 1: 10
// Value of item 2: 100
// Weight of item 2: 20
// Value of item 3: 120
// Weight of item 3: 30
// Enter the knapsack capacity: 50
// output 
// final value :240