/*Assignment 4 :- 
Represent a graph of your college campus using adjacency list /adjacency matrix. Nodes
should represent the various departments and links should represent the distance between
them. Find a minimum spanning tree using Kruskal’s algorithm or using Prim’s
algorithm.

*/

#include <iostream>
using namespace std;

#define INF 9999999  // Define infinity value
#define V 5  // Number of vertices (departments)

string department[V] = {"CS", "ECE", "MECH", "ADMIN", "LIBRARY"};

class Graph {
    int G[V][V];  // Adjacency matrix for the graph

public:
    // Function to read the graph
    void readGraph() {
        cout << "Enter the graph adjacency matrix (5x5 matrix):\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cin >> G[i][j];
            }
        }
    }

    // Function to print the graph (adjacency matrix)
    void printGraph() {
        cout << "\nGraph (Adjacency Matrix):\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << G[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Function to implement Prim's MST algorithm
    void primMST() {
        int visited[V] = {0};  // To track visited departments
        visited[0] = 1;  // Start from department 0 (CS)
        int no_edge = 0;  // Number of edges in the MST
        int totalCost = 0;  // Total cost of the MST

        cout << "Selected Edges : Weight\n";

        // Continue until we have added V-1 edges to the MST
        while (no_edge < V - 1) {
            int min_weight_edge = INF;  // Initialize min weight to a large number
            int row = -1, col = -1;

            // Find the minimum weight edge connecting a visited vertex to an unvisited one
            for (int i = 0; i < V; i++) {
                if (visited[i]) {  // If department i is visited
                    for (int j = 0; j < V; j++) {
                        if (!visited[j] && G[i][j] != 0 && G[i][j] < min_weight_edge) {
                            min_weight_edge = G[i][j];
                            row = i;
                            col = j;
                        }
                    }
                }
            }

            // If a valid edge was found, add it to the MST
            if (row != -1 && col != -1) {
                cout << department[row] << " - " << department[col] << " : " << G[row][col] << endl;
                visited[col] = 1;  // Mark the department as visited
                totalCost += G[row][col];
                no_edge++;  // Increment the number of edges in the MST
            }
        }

        cout << "Total Cost of MST: " << totalCost << endl;
    }
};

int main() {
    Graph campus;

    // Read the graph input
    campus.readGraph();

    // Print the graph adjacency matrix
    campus.printGraph();

    // Call Prim's algorithm to find the MST
    campus.primMST();

    return 0;
}
