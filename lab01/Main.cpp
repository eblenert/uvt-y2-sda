#include <cstdlib>
#include "Node.h"
#include "IODialog.h"
void startProcessing(BSTree*);

int main()
{
    BSTree* tree = new BSTree();
    startProcessing(tree);
    delete tree;
}

void perform(BSTree*, int);

void startProcessing(BSTree* tree)
{
    int op;
    while (true)
    {
        op = IODialog::getTreeOperation();
        perform(tree, op);
    }
}

void perform(BSTree* tree, int op)
{
    list<int> nodeKeys;
    Node* nod;
    int skey;
    switch (op)
    {
    case 1: // Add nodes
        IODialog::getNodeKeys(nodeKeys);
        for (list<int>::iterator it = nodeKeys.begin();
                it !=nodeKeys.end(); it++)
            tree->insert(tree->createNode(*it));
        break;
    case 2: // Delete node
        skey = IODialog::getNodeKey();
        nod = tree->search(tree->root, skey);
        if (nod != 0) tree->del(nod);
        else cout << "Node not found" << endl;
        break;
    case 3: // Get minimum node
        nod = tree->minimum(tree->root);
        if (nod == 0 ) cout << "Minimum not found" << endl;
        else cout << "Minimum is: " << nod->toString() << endl;
        break;
    case 4: // Get maximum node
        nod = tree->maximum(tree->root); // tree->maximum(Node*) must be implemented!
        if (nod == 0) cout << "Maximum not found" << endl;
        else cout << "Maximum is: " << nod->toString() << endl;
        break;
    case 5: // Get successor of specified node
        skey = IODialog::getNodeKey();
        nod = tree->search(tree->root, skey);
        if (nod != 0)
        {
            nod = tree->successor(nod);
            if (nod == Node::Nil) // Found bug?
                cout << "Node with key " << skey << " has no successor.\n";
            else cout << "Successor is: " << nod->toString() << '\n';
        }
        else cout << "Node not found.\n";
        break;
    case 6: // Get predecessor of specified node
        skey = IODialog::getNodeKey();
        nod = tree->search(tree->root, skey);
        if (nod != 0)
        {
            nod = tree->predecessor(nod); // tree->predecessor(Node*) must be implemented!
            if (nod == 0) cout << "Node with key " << skey << " has no predecessor.\n";
            else cout << "Predecessor is: " << nod->toString() << '\n';
        }
        else cout << "Node not found.\n";
        break;
    case 7: // Show the nodes of tree in indented form
        tree->indentedDisplay();
        break;
    case 8:
        cout << "\nInorder traversal of the tree yields" << endl << ' ';
        tree->inorder();
        cout << endl;
        break;
    case 9: // Compute and show tree depth of tree
        // TODO
        cout << "The depth of the tree is " << tree->depth() << endl;
        break;
    case 10: // Exit
        delete tree;
        cout << "Bye!" << endl;
        exit (0);
    }
}
