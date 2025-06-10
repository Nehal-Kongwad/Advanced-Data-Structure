// calculate the height of the tree

#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;
   
    public:
    Node(int d){
    data = d;
    left = NULL;
    right = NULL;
    }
   
    int height(Node *root){
        if(root == NULL){
            return 0;
        }
        if(root->left == NULL && root->right == NULL){
            return 0;
        }
        int hl, hr;
        hl = height(root->left);
        hr = height(root->right);
        if(hl>hr){
            return hl+1;
        }
        return hr+1;

    }
};

int main(){
    Node *root = new Node(100);
    root->left = new Node(50);
    root->right = new Node(70);
    root->left->left = new Node(30);
    root->left->right = new Node(5);
    cout<<root->height(root);
    return 0;
}