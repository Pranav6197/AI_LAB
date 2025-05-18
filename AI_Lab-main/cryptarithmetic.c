#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 10

char word1[MAX_LEN], word2[MAX_LEN], result[MAX_LEN];
char letters[26];
int values[26], letter_count = 0;
bool used[10] = {false};

// Get unique letters from all words
void get_letters() {
    bool seen[26] = {false};
    
    for (int i = 0; word1[i]; i++)
        if (!seen[word1[i] - 'A']) {
            seen[word1[i] - 'A'] = true;
            letters[letter_count++] = word1[i];
        }
    
    for (int i = 0; word2[i]; i++)
        if (!seen[word2[i] - 'A']) {
            seen[word2[i] - 'A'] = true;
            letters[letter_count++] = word2[i];
        }
    
    for (int i = 0; result[i]; i++)
        if (!seen[result[i] - 'A']) {
            seen[result[i] - 'A'] = true;
            letters[letter_count++] = result[i];
        }
    
    for (int i = 0; i < 26; i++)
        values[i] = -1;
}

// Convert word to number based on letter values
int word_to_num(char* word) {
    int num = 0;
    for (int i = 0; word[i]; i++)
        num = num * 10 + values[word[i] - 'A'];
    return num;
}

// Check if solution is valid
bool is_valid() {
    // Leading zeros check
    if (values[word1[0] - 'A'] == 0 || values[word2[0] - 'A'] == 0 || values[result[0] - 'A'] == 0)
        return false;
    
    // Check if equation holds
    return word_to_num(word1) + word_to_num(word2) == word_to_num(result);
}

// Solve using backtracking
bool solve(int pos) {
    if (pos == letter_count)
        return is_valid();
    
    char letter = letters[pos];
    
    for (int d = 0; d <= 9; d++) {
        if (!used[d]) {
            values[letter - 'A'] = d;
            used[d] = true;
            
            if (solve(pos + 1))
                return true;
            
            used[d] = false;
            values[letter - 'A'] = -1;
        }
    }
    
    return false;
}

void print_solution() {
    printf("Solution:\n");
    for (int i = 0; i < letter_count; i++)
        printf("%c = %d\n", letters[i], values[letters[i] - 'A']);
    
    printf("\n%s (%d)\n+ %s (%d)\n= %s (%d)\n", 
           word1, word_to_num(word1),
           word2, word_to_num(word2),
           result, word_to_num(result));
}

int main() {
    printf("Enter first word: ");
    scanf("%s", word1);
    
    printf("Enter second word: ");
    scanf("%s", word2);
    
    printf("Enter result word: ");
    scanf("%s", result);
    
    // Convert to uppercase
    for (int i = 0; word1[i]; i++) if (word1[i] >= 'a') word1[i] -= 32;
    for (int i = 0; word2[i]; i++) if (word2[i] >= 'a') word2[i] -= 32;
    for (int i = 0; result[i]; i++) if (result[i] >= 'a') result[i] -= 32;
    
    get_letters();
    
    if (solve(0))
        print_solution();
    else
        printf("No solution found.\n");
    
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