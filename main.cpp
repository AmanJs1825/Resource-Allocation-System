#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int value;
};

// Function to solve the knapsack problem
int knapsack(int capacity, const vector<Item>& items, vector<bool>& selectedItems) {
    int n = items.size();
    // Create a 2D table to store the maximum value that can be obtained
    // for each sub-problem (i.e., for each capacity and each item)
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Fill the dp table in a bottom-up manner
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                // If the current item can be included, choose the maximum
                // value between including and excluding the item
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            } else {
                // If the current item's weight exceeds the capacity,
                // exclude the item
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Determine the items included in the knapsack
    int remainingCapacity = capacity;
    for (int i = n; i > 0 && remainingCapacity > 0; --i) {
        if (dp[i][remainingCapacity] != dp[i - 1][remainingCapacity]) {
            selectedItems[i - 1] = true;
            remainingCapacity -= items[i - 1].weight;
        }
    }

    // The bottom-right cell of the dp table contains the maximum value
    // that can be obtained with the given capacity and items
    return dp[n][capacity];
}

int main() {
    int capacity;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    int numItems;
    cout << "Enter number of items: ";
    cin >> numItems;

    vector<Item> items(numItems);
    for (int i = 0; i < numItems; ++i) {
        cout << "Enter weight for item " << i + 1 << ": ";
        cin >> items[i].weight;
        cout << "Enter value for item " << i + 1 << ": ";
        cin >> items[i].value;
    }

    vector<bool> selectedItems(numItems, false);
    int max_value = knapsack(capacity, items, selectedItems);

    // Print all inputs
    cout << "\nKnapsack Capacity: " << capacity << endl;
    cout << "Number of Items: " << numItems << endl;
    cout << "Item Details:\n";
    for (int i = 0; i < numItems; ++i) {
        cout << "Item " << i + 1 << ": Weight = " << items[i].weight << ", Value = " << items[i].value;
        if (selectedItems[i]) {
            cout << " (Included in Knapsack)";
        }
        cout << endl;
    }

    // Print item numbers included in the knapsack
    cout << "\nItems included in the knapsack with maximum value:";
    for (int i = 0; i < numItems; ++i) {
        if (selectedItems[i]) {
            cout << " " << i + 1;
        }
    }
    cout << endl;

    cout << "\nMaximum value that can be obtained: " << max_value << endl;

    return 0;
}
