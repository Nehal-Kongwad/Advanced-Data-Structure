#include<iostream>
using namespace std;

class BT{
    public:
    char data;
    BT *lchild;
    BT *rchild;

    BT(char d){
        data = d;
        lchild = NULL;
        rchild = NULL;

    }
};

int main(){
    //creating node using the constructor

    BT *root = new BT('A');
    cout<< root->data<<endl;

    BT *second = new BT('B');
    root->lchild = second;
    
    BT *third = new BT('C');
    root->rchild = third;

    BT *fourth = new BT('D');
    root->lchild->lchild = fourth;

    BT *fifth = new BT('E');
    root->lchild->rchild = fifth;

    BT *sixth = new BT('F');
    root->rchild->rchild = sixth;

    cout<<"The Tree is :- "; 
    cout<<root->data<<" "; //A
    cout<<root->lchild->data<<" "; //B
    cout<<root->rchild->data<<" "; //C
    cout<<root->lchild->lchild->data<<" "; //D
    cout<<root->lchild->rchild->data<<" "; //E
    cout<< root->rchild->rchild->data<<" "; //F

}