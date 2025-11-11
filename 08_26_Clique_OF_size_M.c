#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX 20  // To limit size for reasonable runtime

int graph[MAX][MAX];
int n, e, m;

// Function to check if a given subset of vertices forms a clique
bool isClique(int vertices[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (graph[vertices[i]][vertices[j]] == 0)
                return false;
        }
    }
    return true;
}

// Utility to generate combinations recursively
bool findClique(int start, int currLen, int vertices[]) {
    if (currLen == m) {
        return isClique(vertices, m);
    }

    for (int i = start; i < n; i++) {
        vertices[currLen] = i;
        if (findClique(i + 1, currLen + 1, vertices))
            return true;
    }
    return false;
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter number of edges (e): ");
    scanf("%d", &e);
    printf("Enter clique size to check (m): ");
    scanf("%d", &m);

    if (n > MAX) {
        printf("n too large! Please use n <= %d\n", MAX);
        return 0;
    }

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    int vertices[MAX];
    if (findClique(0
