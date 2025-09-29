#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// ---------- Graph Representation ----------
typedef struct Node {
    int v;
    struct Node* next;
} Node;

Node* adj[MAX];  // adjacency list
int V, E;

// Utility: Add edge (directed if directed=1, undirected if directed=0)
void addEdge(int u, int v, int directed) {
    Node* n1 = (Node*)malloc(sizeof(Node));
    n1->v = v; n1->next = adj[u];
    adj[u] = n1;

    if (!directed) {
        Node* n2 = (Node*)malloc(sizeof(Node));
        n2->v = u; n2->next = adj[v];
        adj[v] = n2;
    }
}

// ---------- Strongly Connected Components (Tarjan’s Algorithm) ----------
int disc[MAX], low[MAX], stackMember[MAX], timeCounter;
int stack[MAX], top = -1;

void SCCUtil(int u) {
    disc[u] = low[u] = ++timeCounter;
    stack[++top] = u;
    stackMember[u] = 1;

    for (Node* p = adj[u]; p != NULL; p = p->next) {
        int v = p->v;
        if (disc[v] == -1) {
            SCCUtil(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (stackMember[v]) {
            if (disc[v] < low[u]) low[u] = disc[v];
        }
    }

    if (low[u] == disc[u]) {
        printf("SCC: ");
        while (stack[top] != u) {
            printf("%d ", stack[top]);
            stackMember[stack[top--]] = 0;
        }
        printf("%d\n", stack[top]);
        stackMember[stack[top--]] = 0;
    }
}

void findSCCs() {
    for (int i = 0; i < V; i++) {
        disc[i] = -1; low[i] = -1; stackMember[i] = 0;
    }
    timeCounter = 0; top = -1;

    printf("\nStrongly Connected Components:\n");
    for (int i = 0; i < V; i++) {
        if (disc[i] == -1)
            SCCUtil(i);
    }
}

// ---------- Biconnected Components, Articulation Points, Bridges ----------
int disc2[MAX], low2[MAX], parent[MAX], time2;
bool ap[MAX];   // articulation points

void BCC_AP_Bridge_Util(int u) {
    int children = 0;
    disc2[u] = low2[u] = ++time2;

    for (Node* p = adj[u]; p != NULL; p = p->next) {
        int v = p->v;

        if (disc2[v] == -1) {
            children++;
            parent[v] = u;
            BCC_AP_Bridge_Util(v);

            if (low2[v] < low2[u]) low2[u] = low2[v];

            // Articulation point condition
            if (parent[u] == -1 && children > 1)
                ap[u] = true;
            if (parent[u] != -1 && low2[v] >= disc2[u])
                ap[u] = true;

            // Bridge condition
            if (low2[v] > disc2[u])
                printf("Bridge: %d -- %d\n", u, v);
        }
        else if (v != parent[u]) {
            if (disc2[v] < low2[u]) low2[u] = disc2[v];
        }
    }
}

void findBCC_AP_Bridges() {
    for (int i = 0; i < V; i++) {
        disc2[i] = -1; low2[i] = -1; parent[i] = -1; ap[i] = false;
    }
    time2 = 0;

    printf("\nBridges and Articulation Points:\n");
    for (int i = 0; i < V; i++) {
        if (disc2[i] == -1)
            BCC_AP_Bridge_Util(i);
    }

    printf("Articulation Points: ");
    for (int i = 0; i < V; i++) {
        if (ap[i]) printf("%d ", i);
    }
    printf("\n");
}

// ---------- Main ----------
int main() {
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    for (int i = 0; i < V; i++) adj[i] = NULL;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v, 1);   // Directed for SCC
    }

    findSCCs();

    // Reset adjacency for undirected (for BCC, articulation points, bridges)
    for (int i = 0; i < V; i++) adj[i] = NULL;

    printf("\nEnter edges again for undirected graph:\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v, 0);
    }

    findBCC_AP_Bridges();

    return 0;
}
OUTPUT:
Enter number of vertices and edges: 5 5
Enter edges (u v):
1 0
0 2
2 1
0 3
3 4

Strongly Connected Components:
SCC: 1 2 0
SCC: 3
SCC: 4

Enter edges again for undirected graph:
0 1
0 2
1 2
0 3
3 4

Bridges and Articulation Points:
Bridge: 3 -- 4
Bridge: 0 -- 3
Articulation Points: 0 3
