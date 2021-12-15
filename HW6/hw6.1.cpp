#include <iostream>
#include <stack>
#include<algorithm>
using namespace std;

class node
{
public:
    node() : left(NULL), right(NULL), cargo(-1) {}
    int cargo;
    node *left;
    node *right;
    void visit() { cout << cargo << " "; }
};

class BinaryTree
{
public:
    BinaryTree() { rootNode = new node; }
    ~BinaryTree() { destroy_tree(rootNode); }
    void replace(unsigned int key, int cargo); // Assume the binary is full, and root is the first, insert if not exist
    void preorder_traverse() { preorder_traverse(rootNode); }
    int getheight(){
        int height = 0, depth =0 ;
        getheight(height, depth, rootNode);
        return height;
    }

private:
    void getheight(int &height, int &depth, node *t);
    void destroy_tree(node *leaf);
    void preorder_traverse(node *t);
    node *rootNode;
};

void BinaryTree::destroy_tree(node *leaf)
{
    if (leaf != NULL)
    {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void BinaryTree::replace(unsigned int key, int car)
{
    if (key == 1)
    {
        rootNode->cargo = car;
        return;
    }
    stack<int> stackpointer;
    unsigned int parent = key;
    while (parent >= 2)
    {
        // cout << parent << " " << parent % 2 << endl;
        stackpointer.push(parent % 2);
        parent = parent / 2;
    }
    node *curpos = rootNode;
    while (!stackpointer.empty())
    {
        int leftorright = stackpointer.top();
        stackpointer.pop();
        if (leftorright == 0)
        {
            if (curpos->left == NULL)
            {
                curpos->left = new node;
            }
            curpos = curpos->left;
        }
        else
        {
            if (curpos->right == NULL)
            {
                curpos->right = new node;
            }
            curpos = curpos->right;
        }
    }
    curpos->cargo = car;
    // cout<< endl;
}

void BinaryTree::preorder_traverse(node *t)
{
    if (t)
    {
        t->visit();
        preorder_traverse(t->left);
        preorder_traverse(t->right);
    }
}

void BinaryTree::getheight(int &height, int &depth, node *t)
{
    if (t){
        depth ++;
        height = max(height, depth);
        getheight(height, depth, t->left);
        getheight(height, depth, t->right);
        depth --;
    }
}

int main()
{
    BinaryTree mytree;
    for (unsigned int k = 1; k < 6; k++)
    {
        mytree.replace(2*k, k);
    }
    mytree.preorder_traverse();
    cout<< endl<< mytree.getheight() <<endl;
    return 0;
}