#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

static const string goalState = "123456780";  // goal: tiles 1–8, blank (0) last
static const int N = 3;

// Generate neighbors by sliding the blank up/down/left/right
vector<string> getNeighbors(const string& s) {
    vector<string> result;
    int zeroPos = s.find('0');
    int zr = zeroPos / N, zc = zeroPos % N;
    static const int dr[4] = {-1, 1, 0, 0};
    static const int dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int nr = zr + dr[i], nc = zc + dc[i];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
            string t = s;
            swap(t[zeroPos], t[nr * N + nc]);
            result.push_back(move(t));
        }
    }
    return result;
}

int main() {
    cout << "Enter initial 8-puzzle (0 for blank), row by row:\n";
    string start;
    for (int i = 0; i < 9; ++i) {
        char c; 
        cin >> c;
        start.push_back(c);
    }

    if (start == goalState) {
        cout << "Already at goal!\n";
        return 0;
    }

    queue<string> q;
    unordered_set<string> visited;
    unordered_map<string, string> parent;

    q.push(start);
    visited.insert(start);
    parent[start] = "";

    bool found = false;
    while (!q.empty()) {
        string cur = q.front(); q.pop();

        for (auto &nbr : getNeighbors(cur)) {
            if (visited.count(nbr)) continue;
            visited.insert(nbr);
            parent[nbr] = cur;
            if (nbr == goalState) {
                found = true;
                break;
            }
            q.push(nbr);
        }
        if (found) break;
    }

    if (!found) {
        cout << "No solution found.\n";
        return 0;
    }

    // Reconstruct path
    vector<string> path;
    for (string s = goalState; !s.empty(); s = parent[s])
        path.push_back(s);
    reverse(path.begin(), path.end());

    // Print steps
    cout << "\nSolution in " << (path.size() - 1) << " moves:\n";
    for (auto &st : path) {
        for (int i = 0; i < 9; ++i) {
            cout << (st[i] == '0' ? '_' : st[i]) << ' ';
            if (i % 3 == 2) cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
