#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

// Declare the structre of the node
struct node {
    int id;
    int holderval;
    node* l;
    node* r;
    node(int id_val) : id(id_val), holderval(id_val), l(nullptr), r(nullptr) {}
};

// Function for Inorder Traversal
void TraversalInorder(const node* roonodeT) {
    if (roonodeT == nullptr) {
        return;
    }
    TraversalInorder(roonodeT->l);
    cout << "Node: " << roonodeT->id << ", Holder: " << roonodeT->holderval << endl;
    TraversalInorder(roonodeT->r);
}

// Function to pass token in Raymond Tree with animation
void token(node* roonodeT, int NodeCS, vector<int>& path) {
    if (roonodeT == nullptr) {
        cout << "Node not found!" << endl;
        return;
    }

    // Store current node in path
    path.push_back(roonodeT->id);

    if (NodeCS == roonodeT->id) {
        // Print animation for token reaching the target
        cout << endl;
        for (size_t i = 0; i < path.size(); ++i) {
            for (size_t j = 0; j < path.size(); ++j) {
                if (j == i) {
                    cout << "*" << path[j] << "* "; // Highlight current node
                } else {
                    cout << path[j] << " ";
                }
                if (j < path.size() - 1) {
                    cout << "-> ";
                }
            }
            cout << endl;
            this_thread::sleep_for(chrono::milliseconds(500)); // 500ms delay
        }
        cout << "Token reached node " << roonodeT->id << endl;
        roonodeT->holderval = roonodeT->id; // Node holds the token
        return;
    }
    else if (NodeCS < roonodeT->id) {
        if (roonodeT->l == nullptr) {
            cout << "Node " << NodeCS << " not found in the tree!" << endl;
            return;
        }
        roonodeT->holderval = roonodeT->l->id; // Update holder to left child
        // Print current step in path
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << " ";
            if (i < path.size() - 1) {
                cout << "-> ";
            }
        }
        cout << "-> *" << roonodeT->l->id << "*" << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // 500ms delay
        token(roonodeT->l, NodeCS, path);
    }
    else {
        if (roonodeT->r == nullptr) {
            cout << "Node " << NodeCS << " not found in the tree!" << endl;
            return;
        }
        roonodeT->holderval = roonodeT->r->id; // Update holder to right child
        // Print current step in path
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << " ";
            if (i < path.size() - 1) {
                cout << "-> ";
            }
        }
        cout << "-> *" << roonodeT->r->id << "*" << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // 500ms delay
        token(roonodeT->r, NodeCS, path);
    }
}

// Function to Insert Node
void NodeTinsert(node* nodeNew, node* roonodeT) {
    if (nodeNew->id > roonodeT->id) {
        if (roonodeT->r == nullptr) {
            roonodeT->r = nodeNew;
            nodeNew->holderval = roonodeT->id; // New node points to parent
        }
        else {
            NodeTinsert(nodeNew, roonodeT->r);
        }
    }
    else if (nodeNew->id < roonodeT->id) {
        if (roonodeT->l == nullptr) {
            roonodeT->l = nodeNew;
            nodeNew->holderval = roonodeT->id; // New node points to parent
        }
        else {
            NodeTinsert(nodeNew, roonodeT->l);
        }
    }
    // Ignore if nodeNew->id == roonodeT->id (duplicate IDs not allowed)
}

// Function to destroy the tree and free memory
void destroyTree(node* roonodeT) {
    if (roonodeT == nullptr) {
        return;
    }
    destroyTree(roonodeT->l);
    destroyTree(roonodeT->r);
    delete roonodeT;
}

// Driver Function
int main() {

    node* roonodeT = nullptr;
    node* nodeNew = nullptr;
    int n, NodeCS, rootId, idValue;
    vector<int> path;

    // Input number of nodes
    cout << "Enter the number of nodes: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of nodes must be positive!" << endl;
        return -1;
    }

    // Input root node ID
    cout << "Enter the ID for the root node: ";
    cin >> rootId;

    // Create root node
    roonodeT = new node(rootId);

    // Input remaining node IDs
    cout << "Enter " << n-1 << " unique node IDs (excluding root " << rootId << "):" << endl;
    for (int i = 1; i < n; ++i) {
        cin >> idValue;
        nodeNew = new node(idValue);
        NodeTinsert(nodeNew, roonodeT);
    }

    // Input node to enter critical section
    cout << "Enter the node for entering CS: ";
    cin >> NodeCS;

    // Print tree structure
    cout << "\nTree structure (Inorder traversal):" << endl;
    TraversalInorder(roonodeT);

    // Process token passing with animation
    cout << "\nToken passing path to node " << NodeCS << ":" << endl;
    token(roonodeT, NodeCS, path);

    // Print final tree structure
    cout << "\nTree structure after token passing:" << endl;
    TraversalInorder(roonodeT);

    // Clean up memory
    destroyTree(roonodeT);

    return 0;
}