#include <stdio.h>
#include <stdbool.h>

#define MAX 50  // Maximum vertices
int graph[MAX][MAX];
int color[MAX];
int n;

// Function to check bipartiteness using BFS
bool isBipartite(int start) {
    int queue[MAX], front = 0, rear = 0;

    color[start] = 0; // Start coloring with 0
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];

        // Check self-loop
        if (graph[u][u] == 1)
            return false;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] == 1) {
                // If vertex v is not colored, assign alternate color
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    queue[rear++] = v;
                }
                // If adjacent vertices have the same color → not bipartite
                else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int e, u, v;
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    // Initialize all vertices as uncolored (-1)
    for (int i = 0; i < n; i++)
        color[i] = -1;

    bool result = true;
    for (int i = 0; i < n; i++) {
        // For disconnected graphs
        if (color[i] == -1) {
            if (!isBipartite(i)) {
                result = false;
                break;
            }
        }
    }

    if (result)
        printf("The graph is Bipartite.\n");
    else
        printf("The graph is NOT Bipartite.\n");

    return 0;
}
