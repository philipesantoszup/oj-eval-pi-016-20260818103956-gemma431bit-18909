#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    map<string, vector<int>> db;

    for (int i = 0; i < n; ++i) {
        string cmd;
        if (!(cin >> cmd)) break;
        if (cmd == "insert") {
            string index;
            int value;
            if (!(cin >> index >> value)) break;
            auto& vals = db[index];
            auto it = lower_bound(vals.begin(), vals.end(), value);
            if (it == vals.end() || *it != value) {
                vals.insert(it, value);
            }
        } else if (cmd == "delete") {
            string index;
            int value;
            if (!(cin >> index >> value)) break;
            if (db.count(index)) {
                auto& vals = db[index];
                auto it = lower_bound(vals.begin(), vals.end(), value);
                if (it != vals.end() && *it == value) {
                    vals.erase(it);
                }
            }
        } else if (cmd == "find") {
            string index;
            if (!(cin >> index)) break;
            if (db.count(index) && !db[index].empty()) {
                const auto& vals = db[index];
                for (size_t j = 0; j < vals.size(); ++j) {
                    cout << vals[j] << (j == vals.size() - 1 ? "" : " ");
                }
                cout << "\n";
            } else {
                cout << "null\n";
            }
        }
    }

    return 0;
}
