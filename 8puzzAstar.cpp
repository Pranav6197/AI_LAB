#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// Dimension of the puzzle
static const int N = 3;
static const string goalState = "123456780";  // goal: numbers 1–8, with 0 as blank at end

// Manhattan-distance heuristic
int heuristic(const string& s) {
    int dist = 0;
    for (int i = 0; i < 9; ++i) {
        char c = s[i];
        if (c == '0') continue;  // skip blank
        int val = c - '1';      // 0-based tile number
        int goalRow = val / N;
        int goalCol = val % N;
        int curRow  = i / N;
        int curCol  = i % N;
        dist += abs(goalRow - curRow) + abs(goalCol - curCol);
    }
    return dist;
}

// A* node
struct Node {
    string state;
    int g;   // cost so far
    int f;   // g + h
    Node(string s, int g_, int f_) : state(move(s)), g(g_), f(f_) {}
};

// Min‑heap by lowest f
struct Compare {
    bool operator()(Node const& a, Node const& b) const {
        return a.f > b.f;
    }
};

// Generate all valid neighbors by sliding the blank
vector<string> neighbors(const string& s) {
    static const int dr[4] = { -1, +1, 0, 0 };
    static const int dc[4] = { 0, 0, -1, +1 };
    vector<string> result;
    int zeroPos = s.find('0');
    int zr = zeroPos / N, zc = zeroPos % N;

    for (int d = 0; d < 4; ++d) {
        int nr = zr + dr[d], nc = zc + dc[d];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
            string t = s;
            swap(t[zeroPos], t[nr * N + nc]);
            result.push_back(move(t));
        }
    }
    return result;
}

int main() {
    cout << "Enter initial 8-puzzle configuration (use 0 for blank), row by row:\n";
    string start;
    for (int i = 0; i < 9; ++i) {
        char c; 
        cin >> c;
        start.push_back(c);
    }

    // A* search structures
    priority_queue<Node, vector<Node>, Compare> openSet;
    unordered_map<string,int> gScore;        // best g found so far
    unordered_map<string,string> cameFrom;   // for path reconstruction

    int h0 = heuristic(start);
    openSet.emplace(start, 0, h0);
    gScore[start] = 0;
    cameFrom[start] = "";  // sentinel

    bool found = false;
    while (!openSet.empty()) {
        Node cur = openSet.top(); openSet.pop();
        if (cur.state == goalState) {
            found = true;
            break;
        }

        // If we have already found a better path to this state, skip
        if (cur.g > gScore[cur.state]) continue;

        // Explore neighbors
        for (auto &nbr : neighbors(cur.state)) {
            int tentative_g = cur.g + 1;
            auto it = gScore.find(nbr);
            if (it == gScore.end() || tentative_g < it->second) {
                gScore[nbr] = tentative_g;
                int f = tentative_g + heuristic(nbr);
                openSet.emplace(nbr, tentative_g, f);
                cameFrom[nbr] = cur.state;
            }
        }
    }

    if (!found) {
        cout << "No solution found.\n";
        return 0;
    }

    // Reconstruct path
    vector<string> path;
    for (string s = goalState; !s.empty(); s = cameFrom[s])
        path.push_back(s);
    reverse(path.begin(), path.end());

    // Print solution
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
