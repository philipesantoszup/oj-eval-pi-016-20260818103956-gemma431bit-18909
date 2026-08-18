#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    map<string, vector<int>> db;

    for (int i = 0; i < n; ++i) {
        string cmd;
        cin >> cmd;
        if (cmd == "insert") {
            string index;
            int value;
            cin >> index >> value;
            auto& vals = db[index];
            if (find(vals.begin(), vals.end(), value) == vals.end()) {
                vals.push_back(value);
                sort(vals.begin(), vals.end());
            }
        } else if (cmd == "delete") {
            string index;
            int value;
            cin >> index >> value;
            if (db.count(index)) {
                auto& vals = db[index];
                auto it = find(vals.begin(), vals.end(), value);
                if (it != vals.end()) {
                    vals.erase(it);
                }
            }
        } else if (cmd == "find") {
            string index;
            cin >> index;
            if (db.count(index) && !db[index].empty()) {
                const auto& vals = db[index];
                for (size_t i = 0; i < vals.size(); ++i) {
                    cout << vals[i] << (i == vals.size() - 1 ? "" : " ");
                }
                cout << "\n";
            } else {
                cout << "null\n";
            }
        }
    }

    return 0;
}
