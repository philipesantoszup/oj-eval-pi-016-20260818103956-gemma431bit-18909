#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

const string DB_FILE = "database.db";

void save_db(const map<string, vector<int>>& db) {
    ofstream out(DB_FILE, ios::binary);
    for (auto const& [index, vals] : db) {
        size_t idx_len = index.size();
        out.write(reinterpret_cast<const char*>(&idx_len), sizeof(idx_len));
        out.write(index.data(), idx_len);
        size_t vals_size = vals.size();
        out.write(reinterpret_cast<const char*>(&vals_size), sizeof(vals_size));
        out.write(reinterpret_cast<const char*>(vals.data()), vals_size * sizeof(int));
    }
}

void load_db(map<string, vector<int>>& db) {
    ifstream in(DB_FILE, ios::binary);
    if (!in) return;
    while (in) {
        size_t idx_len;
        if (!in.read(reinterpret_cast<char*>(&idx_len), sizeof(idx_len))) break;
        string index(idx_len, ' ');
        in.read(&index[0], idx_len);
        size_t vals_size;
        in.read(reinterpret_cast<char*>(&vals_size), sizeof(vals_size));
        vector<int> vals(vals_size);
        in.read(reinterpret_cast<char*>(vals.data()), vals_size * sizeof(int));
        db[index] = vals;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<string, vector<int>> db;
    load_db(db);

    int n;
    if (!(cin >> n)) {
        save_db(db);
        return 0;
    }

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
            auto it_map = db.find(index);
            if (it_map != db.end()) {
                auto& vals = it_map->second;
                auto it_val = lower_bound(vals.begin(), vals.end(), value);
                if (it_val != vals.end() && *it_val == value) {
                    vals.erase(it_val);
                }
            }
        } else if (cmd == "find") {
            string index;
            if (!(cin >> index)) break;
            auto it_map = db.find(index);
            if (it_map != db.end() && !it_map->second.empty()) {
                const auto& vals = it_map->second;
                for (size_t j = 0; j < vals.size(); ++j) {
                    cout << vals[j] << (j == vals.size() - 1 ? "" : " ");
                }
                cout << "\n";
            } else {
                cout << "null\n";
            }
        }
    }

    save_db(db);
    return 0;
}
