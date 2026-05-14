#include <iostream>     // For input and output (cin, cout)
#include <queue>        // For queue used in BFS
#include <omp.h>        // OpenMP library for parallel programming

using namespace std;

// Graph stored as adjacency matrix
// graph[i][j] = 1 means node i connected to node j
int graph[10][10];

// Visited array to check node already visited or not
bool visited[10];

// Stores total number of nodes
int nodes;

// ---------------- PARALLEL BFS ----------------

void parallelBFS(int start)
{
    // Queue used in BFS
    queue<int> q;

    // Mark starting node as visited
    visited[start] = true;

    // Insert starting node into queue
    q.push(start);

    cout << "BFS Traversal: ";

    // Run loop until queue becomes empty
    while (!q.empty())
    {
        // Get first element from queue
        int current = q.front();

        // Remove first element from queue
        q.pop();

        // Print current node
        cout << current << " ";

        // Parallel loop using OpenMP
        // Multiple threads process neighbors together
        #pragma omp parallel for
        for (int i = 0; i < nodes; i++)
        {
            // Check:
            // 1. connection exists
            // 2. node not visited
            if (graph[current][i] == 1 && !visited[i])
            {
                // Critical section
                // Only one thread allowed at a time
                #pragma omp critical
                {
                    // Check again to avoid duplicate insertion
                    if (!visited[i])
                    {
                        // Mark node visited
                        visited[i] = true;

                        // Insert node into queue
                        q.push(i);
                    }
                }
            }
        }
    }

    // Move to next line
    cout << endl;
}

// ---------------- PARALLEL DFS ----------------

void parallelDFS(int node)
{
    // Mark current node as visited
    visited[node] = true;

    // Print current node
    cout << node << " ";

    // Parallel loop for neighbors
    #pragma omp parallel for
    for (int i = 0; i < nodes; i++)
    {
        // Check:
        // 1. connection exists
        // 2. node not visited
        if (graph[node][i] == 1 && !visited[i])
        {
            // Critical section for safe recursion
            #pragma omp critical
            {
                // Check again
                if (!visited[i])
                {
                    // Recursive DFS call
                    parallelDFS(i);
                }
            }
        }
    }
}

// ---------------- RESET VISITED ARRAY ----------------

void resetVisited()
{
    // Make all nodes unvisited again
    for (int i = 0; i < nodes; i++)
    {
        visited[i] = false;
    }
}

// ---------------- MAIN FUNCTION ----------------

int main()
{
    // edges = total connections
    // u and v = nodes
    // start = starting node
    int edges;
    int u, v;
    int start;

    // Input total nodes
    cout << "Enter number of nodes: ";
    cin >> nodes;

    // Input total edges
    cout << "Enter number of edges: ";
    cin >> edges;

    // Initialize graph matrix with 0
    // Means initially no connections
    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            graph[i][j] = 0;
        }
    }

    // Input graph edges
    cout << "Enter edges (u v):\n";

    for (int i = 0; i < edges; i++)
    {
        // Example:
        // 0 1
        cin >> u >> v;

        // Create connection
        graph[u][v] = 1;

        // Because graph is undirected
        graph[v][u] = 1;
    }

    // Input starting node
    cout << "Enter starting node: ";
    cin >> start;

    // Run BFS
    parallelBFS(start);

    // Reset visited array before DFS
    resetVisited();

    cout << "DFS Traversal: ";

    // Run DFS
    parallelDFS(start);

    cout << endl;

    // Program finished successfully
    return 0;
}