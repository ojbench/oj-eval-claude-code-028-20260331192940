#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        // Process n operations/queries
        for (int i = 0; i < n; i++) {
            string command;
            cin >> command;

            // Basic command processing
            if (command == "add") {
                // Add operation
                string item;
                cin >> item;
                cout << "Added: " << item << endl;
            } else if (command == "query") {
                // Query operation
                string item;
                cin >> item;
                cout << "Queried: " << item << endl;
            } else if (command == "delete") {
                // Delete operation
                string item;
                cin >> item;
                cout << "Deleted: " << item << endl;
            }
        }
    }

    return 0;
}
