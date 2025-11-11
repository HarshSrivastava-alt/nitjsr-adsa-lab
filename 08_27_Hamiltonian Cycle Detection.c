#include <stdio.h>
#include <stdbool.h>

#define MAX 20  // Max number of vertices

int graph[MAX][MAX];
int path[MAX];
int n;

// Function to check if the current vertex can be added to the Hamiltonian cycle
bool isSafe(int v, int pos) {
    // Check if this vertex is adjacent to the previous vertex in the path
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if the vertex has already been included
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive function to solve Hamiltonian Cycle problem
bool hamiltonianCycleUtil(int pos) {
    // Base case: all vertices included
    if (pos == n) {
        // Check if the last vertex connects back to the first
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as the next candidate
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            // Recur to construct rest of the path
            if (hamiltonianCycleUtil(pos + 1))
                return true;

            // Backtrack
            path[pos] = -1;
        }
    }
    return false;
}

bool hamiltonianCycle() {
    // Initialize path[]
    for (int i = 0; i < n; i++)
        path[i] = -1;

    // Start at vertex 0
    path[0] = 0;

    if (hamiltonianCycleUtil(1)) {
        printf("Hamiltonian Cycle found:\n");
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        printf("%d\n", path[0]);  // Return to start
        return true;
    } else {
        printf("No Hamiltonian Cycle exists.\n");
        return false;
    }
}

int main() {
    int e, u, v;
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    if (n > MAX) {
        printf("n too large! Use n <= %d.\n", MAX);
        return 0;
    }

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

    hamiltonianCycle();
    return 0;
}
