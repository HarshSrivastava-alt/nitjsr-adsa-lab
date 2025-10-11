#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];   // Adjacency matrix
int visited[MAX];    // Visited array
int stack[MAX];      // Stack to store the topological order
int n;               // Number of vertices
int top = -1;        // Stack top pointer

// Function to push vertex into stack
void push(int v) {
    stack[++top] = v;
}

// Function to perform DFS
void dfs(int v) {
    visited[v] = 1;

    for (int i = 0; i < n; i++) {
        if (adj[v][i] == 1 && !visited[i])
            dfs(i);
    }

    // After visiting all adjacent vertices, push this vertex to stack
    push(v);
}

// Function to perform Topological Sort
void topologicalSort() {
    for (int i = 0; i < n; i++) {
        if (!visited[i])
            dfs(i);
    }

    printf("\nTopological Sort Order: ");
    while (top != -1) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}

int main() {
    int edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize adjacency matrix and visited array
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v) meaning edge from u -> v:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &u, &v);
        adj[u][v] = 1;  // Directed edge
    }

    topologicalSort();

    return 0;
}
INPUT:
Enter number of vertices: 6
Enter number of edges: 6
Enter edges (u v):
5 2
5 0
4 0
4 1
2 3
3 1

OUTPUT:
Topological Sort Order: 5 4 2 3 1 0

