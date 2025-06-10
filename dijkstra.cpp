/*Assignment 5 :- 
Consider the scenario of the supply chain management system. The supply chain involves
multiple locations, such as suppliers, warehouses, distribution centers, and retail stores,
connected by transportation networks. Find the shortest possible route using Dijkstra&#39;s
algorithm to optimize transportation path and inventory management.
*/

#include <iostream>
using namespace std;
#define V 5       // Number of supply chain points
#define INF 9999  // Infinity value for unreachable paths


// Location names in the supply chain
string locations[V] = {
    "Supplier", 
    "Warehouse", 
    "DistributionCenter", 
    "RetailStoreA", 
    "RetailStoreB"
};

// Function to find the unvisited vertex with the minimum distance
int minDistance(int dist[], int visited[]) {
    int min = INF, min_index = -1;
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0 && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

// Function to print the shortest paths from source
void printSolution(int dist[], int src) {
    cout << "\nShortest transportation paths from " << locations[src] << ":\n";
    cout << "Location\t\tDistance (cost/time)\n";
    for (int i = 0; i < V; i++) {
        cout << locations[i] << "\t\t" << dist[i] << "\n";
    }
}

// Dijkstra's algorithm implementation
void dijkstra(int graph[V][V], int src) {
    int dist[V];      // Stores shortest distances from source
    int visited[V];   // Marks visited nodes (0 = not visited, 1 = visited)

    // Initialization
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;  // Distance from source to itself is 0

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, src);
}

int main() {
    // Adjacency matrix representing transportation cost/time/distance
    int graph[V][V] = {
        //  S    W    D    RA   RB
        {  0,   10,   0,   0,  15 }, // Supplier
        { 10,    0,   5,   0,   0 }, // Warehouse
        {  0,    5,   0,   7,   3 }, // DistributionCenter
        {  0,    0,   7,   0,   4 }, // RetailStoreA
        { 15,    0,   3,   4,   0 }  // RetailStoreB
    };

    int source;
    cout << "Supply Chain Locations:\n";
    for (int i = 0; i < V; i++)
        cout << i << ": " << locations[i] << "\n";

    cout << "\nEnter source location index (0 to " << V - 1 << "): ";
    cin >> source;

    dijkstra(graph, source);

    return 0;
}
