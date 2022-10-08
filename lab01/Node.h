#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int max (int a, int b) {
    return a > b ? a : b;
}

struct Node
{
    int key;       // key
    Node *p;     // pointer to parent
    Node *left;  // pointer to left child
    Node *right; // pointer to right child

    static Node* Nil;

    Node(int k, Node *l = Nil, Node *r = Nil, Node *parent = Nil) :
        key(k), p(parent), left(l), right(r) { }

    string toString()
    {
        ostringstream os;
        os << key;
        return os.str();
    }

    ~Node()
    {
        if(left != Node::Nil)
            delete left;
        if(right != Node::Nil)
            delete right;
    }
};

Node* Node::Nil = new Node(0);

struct BSTree
{
    Node* root;

    /* Default constructor: creates an empty tree */
    BSTree()
    {
        root = Node::Nil;
    }

    ~BSTree()
    {
        delete root;
    }

    Node* createNode(int key)
    {
        return new Node(key);
    }

    /**
     * return the node with key k from this tree, and null
     * if no such node exists
     */
    Node* search(int k)
    {
        return search(root, k);
    }

    Node* search(Node* w, int key)
    {
        if (w == Node::Nil || w->key == key)
            return w;
        return search( (key < w->key) ? w->left : w->right, key);
    }

    Node* maximum(Node* w)
    {
        Node* x = w;
        while (x->right != Node::Nil)
            x = x->right;
        return x;
    }

    Node* minimum(Node* w)
    {
        Node* x = w;
        while (x->left != Node::Nil)
            x = x->left;
        return x;
    }

    /**
     * return a pointer to the successor of node w in
     * this binary search tree
     */
    Node* successor(Node* w)
    {
        Node* x = w;
        if (x->right != Node::Nil) return minimum(x->right);
        if (x->p == Node::Nil)
            return Node::Nil; // x has no successor
        Node* y = x->p;
        while (y != Node::Nil && x == y->right)
        {
            x = y;
            y = y->p;
        }
        return y;
    }

    /**
     * return a pointer to the predecessor of node w in
     * this binary search tree
     */
    Node* predecessor(Node* w)
    {
        Node* x = w;
        if (x->left != Node::Nil) {
            return maximum(x->left);
        }

        if (x->p == Node::Nil) {
            return Node::Nil;
        }

        Node* y = x->p;

        while(y != Node::Nil && x==y->left)
        {
            x = y;
            y = y->p;
        }
        return y;
    }

    /*
     * Insert node z at the right place in the binary search tree
     */
    void insert(Node* z)
    {
        Node *y = Node::Nil;
        Node *x = root;
        while (x != Node::Nil)
        {
            y = x;
            x = (z->key < x->key) ? x->left : x->right;
        }
        z->p = y;
        if (y == Node::Nil)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }

    /**
     * Removes node z from this tree
     */
    Node* del(Node* z)
    {
        Node *y = (z->left == Node::Nil || z->right == Node::Nil) ? z : successor(z);
        Node *x = (y->left != Node::Nil) ? y->left : y->right;
        x->p = y->p;
        if (y->p == Node::Nil)
        {
            root = x;
        }
        else
        {
            if (y == y->p->left)
                y->p->left = x;
            else
                y->p->right = z;
        }
        if (y != z)
        {
            z->key = y->key;
        }
        return y;
    }

    /**
     * This method performs the traversal in inorder
     * of the nodes of a binary tree.
     */
    void inorder(Node* T)
    {
        if (T != Node::Nil)
        {
            inorder(T->left);
            cout << T->toString() << ' ';
            inorder(T->right);
        }
    }

    void inorder()
    {
        inorder(root);
    }

    /**
     * Auxiliary method to display the content of a binary tree
     * in an indented way.
     */
    void display(Node* w, int indent)
    {
        if (w != Node::Nil)
        {
            display(w->right, indent + 2);
            for (int i = 0; i < indent; i++) cout << ' ';
            cout << w->toString() << '\n';
            display(w->left, indent + 2);
        }
    }

    void indentedDisplay()
    {
        cout << "The binary search tree is" <<endl;
        display(root, 0);
    }

    int depth()
    {
        return depth(root);
    }

    int depth(Node* n)
    {
        if (n == Node::Nil) {
            return -1;
        }

        int leftDepth =  depth(n->left);
        int rightDepth = depth(n->right);
        
        return max(leftDepth, rightDepth) + 1;
        
    }
};

#endif /* NODE_H_ */
