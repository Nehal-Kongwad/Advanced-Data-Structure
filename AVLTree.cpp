/* Assignment 2 :-

Implement a multiplayer game system that uses an AVL tree data structure to organize and manage player data efficiently. The multiplayer game supports multiple players participating simultaneously, and the AVL tree is used to store player information such as player_id and scores (key, value pair). The system should provide following operation: 
1. Player Registration 
2. Leaderboard Display 
3. Remove player from game 

*/

#include <iostream>
using namespace std;

class AVL {
public:
    int data;      // Player ID
    int score;     // Player Score
    int ht;
    AVL *Lchild;
    AVL *Rchild;

    AVL() { // Default constructor
        data = 0;
        score = 0;
        ht = 1;
        Lchild = NULL;
        Rchild = NULL;
    }

    AVL(int id, int sc) { // Parameterized constructor
        data = id;
        score = sc;
        ht = 1;
        Lchild = NULL;
        Rchild = NULL;
    }

    int getHgt(AVL *root) { // Calculates height
        if (root == NULL)
            return 0;
        return 1 + max(getHgt(root->Lchild), getHgt(root->Rchild));
    }

    int balfact(AVL *node) { // Calculate balance factor
        if (node == NULL)
            return 0;
        return getHgt(node->Lchild) - getHgt(node->Rchild);
    }

    AVL* RightRotation(AVL *y) { // Right Rotation
        AVL *x = y->Lchild;
        AVL *T2 = x->Rchild;

        // Perform rotation
        x->Rchild = y;
        y->Lchild = T2;

        // Update heights
        y->ht = max(getHgt(y->Lchild), getHgt(y->Rchild)) + 1;
        x->ht = max(getHgt(x->Lchild), getHgt(x->Rchild)) + 1;

        // Return new root
        return x;
    }

    AVL* LeftRotation(AVL *y) { // Left Rotation
        AVL *x = y->Rchild;
        AVL *T2 = x->Lchild;

        // Perform rotation
        x->Lchild = y;
        y->Rchild = T2;

        // Update heights
        y->ht = max(getHgt(y->Lchild), getHgt(y->Rchild)) + 1;
        x->ht = max(getHgt(x->Lchild), getHgt(x->Rchild)) + 1;

        // Return new root
        return x;
    }

    AVL* insert(AVL *node, int id, int sc) {
        if (node == NULL)
            return new AVL(id, sc);

        if (id < node->data)
            node->Lchild = insert(node->Lchild, id, sc);
        else if (id > node->data)
            node->Rchild = insert(node->Rchild, id, sc);
        else
            return node; // Duplicate IDs not allowed

        node->ht = max(getHgt(node->Lchild), getHgt(node->Rchild)) + 1;
        int bl = balfact(node);

        // Balance the tree
        if (bl > 1 && id < node->Lchild->data) // LL Case
            return RightRotation(node);
        if (bl < -1 && id > node->Rchild->data) // RR Case
            return LeftRotation(node);
        if (bl > 1 && id > node->Lchild->data) { // LR Case
            node->Lchild = LeftRotation(node->Lchild);
            return RightRotation(node);
        }
        if (bl < -1 && id < node->Rchild->data) { // RL Case
            node->Rchild = RightRotation(node->Rchild);
            return LeftRotation(node);
        }

        return node;
    }

    AVL* Delete(AVL *root, int key) {
        if (root == NULL)
            return root;

        if (key < root->data)
            root->Lchild = Delete(root->Lchild, key);
        else if (key > root->data)
            root->Rchild = Delete(root->Rchild, key);
        else {
            if (root->Lchild == NULL) {
                AVL *temp = root->Rchild;
                delete root;
                return temp;
            }
            else if (root->Rchild == NULL) {
                AVL *temp = root->Lchild;
                delete root;
                return temp;
            }
            else {
                AVL *temp = root->Rchild;
                while (temp->Lchild != NULL)
                    temp = temp->Lchild;
                root->data = temp->data;
                root->score = temp->score;
                root->Rchild = Delete(root->Rchild, temp->data);
            }
        }

        if (root == NULL)
            return root;

        root->ht = max(getHgt(root->Lchild), getHgt(root->Rchild)) + 1;
        int bal = balfact(root);

        // Balance the tree
        if (bal > 1 && balfact(root->Lchild) >= 0) // LL Case
            return RightRotation(root);
        if (bal < -1 && balfact(root->Rchild) <= 0) // RR Case
            return LeftRotation(root);
        if (bal > 1 && balfact(root->Lchild) < 0) { // LR Case
            root->Lchild = LeftRotation(root->Lchild);
            return RightRotation(root);
        }
        if (bal < -1 && balfact(root->Rchild) > 0) { // RL Case
            root->Rchild = RightRotation(root->Rchild);
            return LeftRotation(root);
        }

        return root;
    }

    void inorder(AVL *root) { // Display leaderboard
        if (root != NULL) {
            inorder(root->Lchild);
            cout << "Player ID: " << root->data << ", Score: " << root->score << endl;
            inorder(root->Rchild);
        }
    }
};

int main() {
    AVL *root = NULL;
    AVL obj;
    int choice, id, score;

    do {
        cout << "\n1. Register Player";
        cout << "\n2. Display Leaderboard";
        cout << "\n3. Remove Player";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Player ID and Score: ";
                cin >> id >> score;
                root = obj.insert(root, id, score);
                break;

            case 2:
                cout << "Leaderboard:\n";
                obj.inorder(root);
                break;

            case 3:
                cout << "Enter Player ID to Remove: ";
                cin >> id;
                root = obj.Delete(root, id);
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
