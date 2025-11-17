#include <stdio.h>
#include <string.h>

// Function to compute the LPS (Longest Prefix Suffix) array
void computeLPS(char pattern[], int m, int lps[]) {
    int len = 0;     // length of previous longest prefix suffix
    lps[0] = 0;      // lps[0] is always 0

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];   // Try shorter prefix
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Pattern Searching Algorithm
void KMP(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    int lps[m];
    computeLPS(pattern, m, lps);

    int i = 0;  // index for text
    int j = 0;  // index for pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];  // continue searching
        } 
        else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    printf("TEXT: %s\n", text);
    printf("PATTERN: %s\n", pattern);

    KMP(text, pattern);

    return 0;
}


OUTPUT:
TEXT: ABABDABACDABABCABAB
PATTERN: ABABCABAB
Pattern found at index 10
