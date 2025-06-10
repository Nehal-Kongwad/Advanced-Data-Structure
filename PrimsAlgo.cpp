/*Assignment 4:-
Represent a graph of your college campus using adjacency list /adjacency matrix. Nodes
should represent the various departments and links should represent the distance between
them. Find a minimum spanning tree using Kruskal’s algorithm or using Prim’s
algorithm.
*/

#include <iostream>
using namespace std;

#define INF 9999999
#define V 5  // Number of vertices in the graph

class Graph {
private:
    int G[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

public:
    void readGraph() {
        cout << "Enter adjacency matrix:" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cin >> G[i][j];
            }
        }
    }

    void printGraph() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << G[i][j] << " ";
            }
            cout << endl;
        }
    }

    void prims() {
        int no_edge = 0, totalCost = 0;
        int visited[V] = {0}; // Initially all vertices are unvisited
        visited[0] = 1; // Start from the first vertex

        cout << "Minimum Selected Edges : Weight" << endl;

        while (no_edge < V - 1) {
            int min = INF;
            int row = -1, col = -1;

            for (int i = 0; i < V; i++) {
                if (visited[i]) {
                    for (int j = 0; j < V; j++) {
                        if (!visited[j] && G[i][j] && G[i][j] < min) {
                            min = G[i][j];
                            row = i;
                            col = j;
                        }
                    }
                }
            }

            if (row != -1 && col != -1) {
                cout << row << " - " << col << " : " << G[row][col] << endl;
                visited[col] = 1;
                totalCost += G[row][col];
                no_edge++;
            }
        }

        cout << "Total cost of MST: " << totalCost << endl;
    }
};

int main() {
    Graph g;
    // g.readGraph();
    // g.printGraph();
    g.prims();
    return 0;
}
