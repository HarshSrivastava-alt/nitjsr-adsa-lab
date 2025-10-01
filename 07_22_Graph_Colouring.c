#include <stdio.h>
#include <stdbool.h>

#define MAX 20   // maximum number of vertices

int graph[MAX][MAX];   // adjacency matrix
int color[MAX];        // assigned colors
int V;                 // number of vertices
int m;                 // number of colors


bool isSafe(int v, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) {
            return false;
        }
    }
    return true;
}

// Recursive function to solve the m-coloring problem
bool graphColoringUtil(int v) {
    if (v == V)   // all vertices are colored
        return true;

    // Try different colors for vertex v
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            color[v] = c;

            if (graphColoringUtil(v + 1))
                return true;

            // Backtrack
            color[v] = 0;
        }
    }
    return false;
}

// Function to solve the graph coloring problem
void graphColoring() {
    for (int i = 0; i < V; i++)
        color[i] = 0;   // initialize all colors as unassigned

    if (graphColoringUtil(0) == false) {
        printf("Solution does not exist with %d colors.\n", m);
        return;
    }

    // Print solution
    printf("Graph coloring possible with %d colors:\n", m);
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i, color[i]);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter number of colors: ");
    scanf("%d", &m);

    graphColoring();

    return 0;
}
OUTPUT:
Enter number of vertices: 4
Enter adjacency matrix (4 x 4):
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
Enter number of colors: 3

Graph coloring possible with 3 colors:
Vertex 0 ---> Color 1
Vertex 1 ---> Color 2
Vertex 2 ---> Color 3
Vertex 3 ---> Color 2
