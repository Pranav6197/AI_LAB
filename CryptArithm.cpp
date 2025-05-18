#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

// Convert a word to number using the letter-to-digit mapping
long long wordToNumber(const string &word, const unordered_map<char, int> &mapping) {
    long long number = 0;
    for (char c : word) {
        number = number * 10 + mapping.at(c);
    }
    return number;
}

// Backtracking function to solve the cryptarithmetic puzzle
bool solve(vector<char> &letters, unordered_map<char, int> &mapping, set<int> &used,
           const string &word1, const string &word2, const string &result, int idx) {

    if (idx == letters.size()) {
        // Check leading zero constraint
        if ((mapping[word1[0]] == 0) || (mapping[word2[0]] == 0) || (mapping[result[0]] == 0))
            return false;

        long long num1 = wordToNumber(word1, mapping);
        long long num2 = wordToNumber(word2, mapping);
        long long res  = wordToNumber(result, mapping);

        return (num1 + num2 == res);
    }

    for (int digit = 0; digit <= 9; ++digit) {
        if (used.count(digit)) continue;

        mapping[letters[idx]] = digit;
        used.insert(digit);

        if (solve(letters, mapping, used, word1, word2, result, idx + 1))
            return true;

        // Backtrack
        used.erase(digit);
        mapping[letters[idx]] = -1;
    }

    return false;
}

int main() {
    string word1, word2, result;
    cout << "Enter first word: ";
    cin >> word1;
    cout << "Enter second word: ";
    cin >> word2;
    cout << "Enter result word: ";
    cin >> result;

    // Collect unique characters
    set<char> uniqueLetters;
    for (char c : word1) uniqueLetters.insert(c);
    for (char c : word2) uniqueLetters.insert(c);
    for (char c : result) uniqueLetters.insert(c);

    if (uniqueLetters.size() > 10) {
        cout << "Too many unique letters! (max 10 allowed)\n";
        return 1;
    }

    vector<char> letters(uniqueLetters.begin(), uniqueLetters.end());
    unordered_map<char, int> mapping;
    set<int> used;

    for (char c : letters)
        mapping[c] = -1;

    if (solve(letters, mapping, used, word1, word2, result, 0)) {
        cout << "\nSolution found:\n";
        for (auto &p : mapping) {
            cout << p.first << " = " << p.second << "\n";
        }
        long long num1 = wordToNumber(word1, mapping);
        long long num2 = wordToNumber(word2, mapping);
        long long res  = wordToNumber(result, mapping);
        cout << "\nCheck: " << num1 << " + " << num2 << " = " << res << "\n";
    } else {
        cout << "No solution exists.\n";
    }

    
    return 0;
}


// Enter first word: SEND
// Enter second word: MORE
// Enter result word: MONEY

// Solution:
// S = 9
// E = 5
// N = 6
// D = 7
// M = 1
// O = 0
// R = 8
// Y = 2

// SEND (9567)
// + MORE (1085)
// = MONEY (10652)



// Enter first word: AAA
// Enter second word: BBB
// Enter result word: CC

// No solution found.