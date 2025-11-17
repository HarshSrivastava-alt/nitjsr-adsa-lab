#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256

// Function to create the bad character table
void badCharHeuristic(char *pattern, int m, int badChar[]) {
    int i;

    // Initialize all occurrences to -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badChar[i] = -1;

    // Fill the actual value of last occurrence
    for (i = 0; i < m; i++)
        badChar[(unsigned char)pattern[i]] = i;
}

// Boyer–Moore Algorithm (Bad Character Heuristic)
void boyerMoore(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int badChar[NO_OF_CHARS];
    badCharHeuristic(pattern, m, badChar);

    int s = 0; // shift of the pattern over text

    while (s <= (n - m)) {
        int j = m - 1;

        // Move from right to left of the pattern
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        // If the pattern is present at current shift
        if (j < 0) {
            printf("Pattern found at index %d\n", s);

            // Shift the pattern
            s += (s + m < n) ? m - badChar[(unsigned char)text[s + m]] : 1;

        } else {
            // Apply bad character shift
            s += (j - badChar[(unsigned char)text[s + j]] > 1) ?
                    j - badChar[(unsigned char)text[s + j]] : 1;
        }
    }
}

int main() {
    char text[] = "ABAAABCD";
    char pattern[] = "ABC";

    printf("TEXT: %s\n", text);
    printf("PATTERN: %s\n", pattern);

    boyerMoore(text, pattern);

    return 0;
}

OUTPUT:
TEXT: ABAAABCD
PATTERN: ABC
Pattern found at index 4
