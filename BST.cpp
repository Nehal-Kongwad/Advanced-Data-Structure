/* Assignment 1 :-

Consider the Dictionary Implementations which allow for efficient storage and retrieval of
key-value pairs using binary search trees. Each node in the tree store (key, value) pair. The
dictionary should support the following operations efficiently:
1. Insert word (Handle insertion of duplicate entry)
2. Delete word
3. Search specific word
4. Display dictionary (Traversal)
5. Mirror image of dictionary 
6. Create a copy of dictionary 
7. Display dictionary level wise
*/


#include<iostream>
using namespace std;

class Node{
public:
    int key;
    int value;
    Node* left;
    Node* right;

    Node(int k, int v){
        key = k;
        value = v;
        left = right = NULL;
    }
};

Node* insert(Node* root, int key, int value){
    if(root == NULL)
        return new Node(key, value);
    if(root->key == key)
        return root;

    if(key < root->key)
        root->left = insert(root->left, key, value);
    else if(key > root->key)
        root->right = insert(root->right, key, value);

    else
        root->value = value; // update value if key already exists

    return root;
}

Node* searchNode(Node* root, int key){
    if(root == NULL || root->key == key)
        return root;

    if(key < root->key)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}

Node* minValueNode(Node* root){
    while(root->left != NULL)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key){
    if(root == NULL)
        return root;

    if(key < root->key)
        root->left = deleteNode(root->left, key);
    else if(key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if(root->left == NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL){
            Node* temp = root->left;
            delete root;
            return temp;
        }
// to delete node having 2 child
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void inorder(Node* root){
    if(root != NULL){
        inorder(root->left);
        cout << root->key << ":" << root->value << " ";
        inorder(root->right);
    }
}

Node* mirror(Node* root){
    if(root == NULL)
        return NULL;

    Node* mirrored = new Node(root->key, root->value);
    mirrored->left = mirror(root->right);
    mirrored->right = mirror(root->left);
    return mirrored;
}

Node* copyTree(Node* root){
    if(root == NULL)
        return NULL;

    Node* copied = new Node(root->key, root->value);
    copied->left = copyTree(root->left);
    copied->right = copyTree(root->right);
    return copied;
}

int height(Node* root){
    if(root == NULL)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

void printLevel(Node* root, int level){
    if(root == NULL)
        return;
    if(level == 1)
        cout << root->key << ":" << root->value << " ";
    else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void levelOrder(Node* root){
    int h = height(root);
    for(int i = 1; i <= h; i++){
        printLevel(root, i);
        cout << endl;
    }
}

int main(){
    Node* root = NULL;
    Node* copiedRoot = NULL;
    Node* mirroredRoot = NULL;

    int choice, key, value;

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert Word\n";
        cout << "2. Delete Word\n";
        cout << "3. Search Word\n";
        cout << "4. Display Dictionary (Inorder)\n";
        cout << "5. Mirror Image of Dictionary\n";
        cout << "6. Create a Copy of Dictionary\n";
        cout << "7. Display Dictionary Level-wise\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Enter key and value to insert: ";
                cin >> key >> value;
                root = insert(root, key, value);
                cout << "Inserted.\n";
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                cout << "Deleted if key existed.\n";
                break;
            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                {
                    Node* found = searchNode(root, key);
                    if(found)
                        cout << "Found: " << found->key << " -> " << found->value << endl;
                    else
                        cout << "Key not found.\n";
                }
                break;
            case 4:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 5:
                mirroredRoot = mirror(root);
                cout << "Mirrored Dictionary (Inorder): ";
                inorder(mirroredRoot);
                cout << endl;
                break;
            case 6:
                copiedRoot = copyTree(root);
                cout << "Copied Dictionary (Inorder): ";
                inorder(copiedRoot);
                cout << endl;
                break;
            case 7:
                cout << "Level-wise Dictionary:\n";
                levelOrder(root);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while(choice != 0);

    return 0;
}
