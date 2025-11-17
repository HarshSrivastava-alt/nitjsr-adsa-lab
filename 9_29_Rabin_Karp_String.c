#include <stdio.h>
#include <string.h>

#define d 256               // number of characters in input alphabet
#define q 101               // A prime number for modulo operations

void rabinKarp(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    int i, j;
    int p = 0;   // hash value for pattern
    int t = 0;   // hash value for text
    int h = 1;

    // The value of h = (d^(m-1)) % q
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate hash value for pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over the text one by one
    for (i = 0; i <= n - m; i++) {

        // If hash values match, check characters
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == m)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate the hash value for the next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + 1 + m - 1]) % q;

            // We might get a negative value, convert it to positive
            if (t < 0)
                t = t + q;
        }
    }
}

int main() {
    char text[] = "ABCCDDAEFG";
    char pattern[] = "CDD";

    printf("TEXT: %s\n", text);
    printf("PATTERN: %s\n", pattern);

    rabinKarp(text, pattern);
    return 0;
}

OUTPUT:
TEXT: ABCCDDAEFG
PATTERN: CDD
Pattern found at index 3
