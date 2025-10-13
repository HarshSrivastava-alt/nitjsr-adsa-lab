#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define INF 999999
#define MAX 20  // maximum for DP (for larger N, runtime grows exponentially)

// Function to find minimum of two values
int min(int a, int b) {
    return (a < b) ? a : b;
}

// TSP recursive function with memoization
int tsp(int mask, int pos, int n, int dist[MAX][MAX], int dp[MAX][1 << MAX]) {
    if (mask == (1 << n) - 1)
        return dist[pos][0];  // return to start

    if (dp[pos][mask] != -1)
        return dp[pos][mask];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city, n, dist, dp);
            ans = min(ans, newAns);
        }
    }
    return dp[pos][mask] = ans;
}

void generateGraph(int n, int dist[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = rand() % 100 + 1;  // random distance between 1–100
        }
    }
}

int main() {
    srand(time(0));
    int sizes[] = {10, 20, 40, 60, 100};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Travelling Salesperson Problem using Dynamic Programming\n");
    printf("-------------------------------------------------------\n");
    printf("Nodes\tExecution Time (seconds)\n");

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];

        if (n > MAX) {
            printf("%d\tToo large for DP solution\n", n);
            continue;
        }

        int dist[MAX][MAX];
        generateGraph(n, dist);

        int dp[MAX][1 << MAX];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < (1 << n); j++)
                dp[i][j] = -1;

        clock_t start = clock();
        int result = tsp(1, 0, n, dist, dp);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t%lf\n", n, time_taken);
    }

    return 0;
}

OUTPUT:
Travelling Salesperson Problem using Dynamic Programming
-------------------------------------------------------
Nodes   Execution Time (seconds)
10      0.002000
20      0.547000
40      Too large for DP solution
60      Too large for DP solution
100     Too large for DP solution
