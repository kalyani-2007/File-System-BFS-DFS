
#include <stdio.h>
#include <string.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
char nodes[MAX][30];
int n, found;

int getNode(char name[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(nodes[i], name) == 0)
            return i;
    }
    return -1;
}

void BFS(int start, char target[]) {
    int queue[MAX], front = 0, rear = 0;
    int seen[MAX] = {0};
    int targetIndex = getNode(target);

    queue[rear++] = start;
    seen[start] = 1;
    found = 0;

    printf("\nBFS Traversal: ");

    while (front < rear) {
        int current = queue[front++];
        printf("%s ", nodes[current]);

        if (current == targetIndex)
            found = 1;

        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !seen[i]) {
                queue[rear++] = i;
                seen[i] = 1;
            }
        }
    }

    printf("\nBFS: File %s\n",
           found ? "FOUND" : "NOT FOUND");
}

void DFS(int current, char target[]) {
    visited[current] = 1;
    printf("%s ", nodes[current]);

    if (strcmp(nodes[current], target) == 0)
        found = 1;

    for (int i = 0; i < n; i++) {
        if (graph[current][i] && !visited[i])
            DFS(i, target);
    }
}

int main() {
    int edges, u, v;
    char startName[30], target[30];

    printf("Number of nodes: ");
    scanf("%d", &n);

    printf("Enter node names (no spaces):\n");
    for (int i = 0; i < n; i++)
        scanf("%29s", nodes[i]);

    printf("Number of connections: ");
    scanf("%d", &edges);

    printf("Enter connections (node1 node2):\n");
    for (int i = 0; i < edges; i++) {
        char a[30], b[30];
        scanf("%29s %29s", a, b);

        u = getNode(a);
        v = getNode(b);

        if (u != -1 && v != -1) {
            graph[u][v] = 1;
            graph[v][u] = 1;
        }
    }

    printf("Starting node: ");
    scanf("%29s", startName);

    printf("File to search: ");
    scanf("%29s", target);

    int start = getNode(startName);

    if (start == -1) {
        printf("Invalid starting node!\n");
        return 0;
    }

    if (getNode(target) == -1)
        printf("Target is not in the graph.\n");

    BFS(start, target);

    memset(visited, 0, sizeof(visited));
    found = 0;

    printf("\nDFS Traversal: ");
    DFS(start, target);

    printf("\nDFS: File %s\n",
           found ? "FOUND" : "NOT FOUND");

    return 0;
}
