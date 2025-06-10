/*Assignment 3:-
Consider the scenario of a maze. The maze is represented as a grid of cells, where each cell can be either 
open or blocked. Each cell in the maze represents a vertex. The goal is to find a path from the starting point 
to the goal within a given maze using DFS and BFS. 
*/

#include <iostream>
using namespace std;

#define MAX 100

int rows, cols;
int maze[MAX][MAX];

// Movement directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y, bool visited[MAX][MAX]) {
    return x >= 0 && y >= 0 && x < rows && y < cols &&
           maze[x][y] == 0 && !visited[x][y];
}

void BFS(int startX, int startY, int goalX, int goalY) {
    bool visited[MAX][MAX] = {false};
    int queueX[MAX * MAX], queueY[MAX * MAX];
    int front = 0, rear = 0;

    queueX[rear] = startX;
    queueY[rear] = startY;
    rear++;
    visited[startX][startY] = true;

    cout << "BFS Path:\n";

    while (front < rear) {
        int x = queueX[front];
        int y = queueY[front];
        front++;

        cout << "(" << x << "," << y << ") ";

        if (x == goalX && y == goalY) {
            cout << "\nReached the goal using BFS!\n";
            return;
        }

        for (int dir = 0; dir < 4; dir++) {
            int newX = x + dx[dir];
            int newY = y + dy[dir];

            if (isValid(newX, newY, visited)) {
                visited[newX][newY] = true;
                queueX[rear] = newX;
                queueY[rear] = newY;
                rear++;
            }
        }
    }

    cout << "\nNo path found using BFS.\n";
}

void DFS(int startX, int startY, int goalX, int goalY) {
    bool visited[MAX][MAX] = {false};
    int stackX[MAX * MAX], stackY[MAX * MAX];
    int top = -1;

    stackX[++top] = startX;
    stackY[top] = startY;

    cout << "DFS Path:\n";

    while (top >= 0) {
        int x = stackX[top];
        int y = stackY[top];
        top--;

        if (!visited[x][y]) {
            visited[x][y] = true;
            cout << "(" << x << "," << y << ") ";

            if (x == goalX && y == goalY) {
                cout << "\nReached the goal using DFS!\n";
                return;
            }

            for (int dir = 3; dir >= 0; dir--) { // reverse order for DFS
                int newX = x + dx[dir];
                int newY = y + dy[dir];

                if (isValid(newX, newY, visited)) {
                    stackX[++top] = newX;
                    stackY[top] = newY;
                }
            }
        }
    }

    cout << "\nNo path found using DFS.\n";
}

int main() {
    int startX, startY, goalX, goalY, choice;

    cout << "Enter number of rows and columns: ";
    cin >> rows >> cols;

    cout << "Enter the maze (0 = open, 1 = blocked):\n";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> maze[i][j];

    cout << "Enter start coordinates (x y): ";
    cin >> startX >> startY;

    cout << "Enter goal coordinates (x y): ";
    cin >> goalX >> goalY;

    do {
        cout << "\n--- Maze Solver Menu ---\n";
        cout << "1. Solve using BFS\n";
        cout << "2. Solve using DFS\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                BFS(startX, startY, goalX, goalY);
                break;
            case 2:
                DFS(startX, startY, goalX, goalY);
                break;
            case 3:
                cout << "Exiting Maze Solver.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
