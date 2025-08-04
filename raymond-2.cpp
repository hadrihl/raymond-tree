    #include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>

using namespace std;

// Structure of the node
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

// Function to calculate tree height for ASCII art
int getHeight(const node* roonodeT) {
    if (roonodeT == nullptr) return 0;
    return 1 + max(getHeight(roonodeT->l), getHeight(roonodeT->r));
}

// Function to print ASCII art of the tree
void printTreeASCII(const node* roonodeT, const vector<int>& path, int level = 0, const string& prefix = "", bool isLast = true) {
    if (roonodeT == nullptr) return;

    // Print current node
    string marker = (find(path.begin(), path.end(), roonodeT->id) != path.end()) ? "**" : "  ";
    cout << prefix << (isLast ? "└── " : "├── ") << marker << roonodeT->id << marker << endl;

    // Prepare prefix for children
    string newPrefix = prefix + (isLast ? "    " : "│   ");

    // Collect children
    vector<node*> children;
    if (roonodeT->l) children.push_back(roonodeT->l);
    if (roonodeT->r) children.push_back(roonodeT->r);

    // Print children
    for (size_t i = 0; i < children.size(); ++i) {
        bool lastChild = (i == children.size() - 1);
        printTreeASCII(children[i], path, level + 1, newPrefix, lastChild);
    }
}

// Function to pass token in Raymond Tree with ASCII art animation
void token(node* roonodeT, int NodeCS, vector<int>& path) {
    if (roonodeT == nullptr) {
        cout << "Node not found!" << endl;
        return;
    }

    // Store current node in path
    path.push_back(roonodeT->id);

    // Clear screen for animation (platform-dependent, using ANSI escape codes)
    cout << "\033[2J\033[1;1H"; // Clear screen and move cursor to top-left
    cout << "Token passing to node " << NodeCS << ":" << endl;
    printTreeASCII(roonodeT, path);
    this_thread::sleep_for(chrono::milliseconds(500)); // 500ms delay

    if (NodeCS == roonodeT->id) {
        cout << "\nToken reached node " << roonodeT->id << endl;
        roonodeT->holderval = roonodeT->id; // Node holds the token
        return;
    }
    else if (NodeCS < roonodeT->id) {
        if (roonodeT->l == nullptr) {
            cout << "Node " << NodeCS << " not found in the tree!" << endl;
            return;
        }
        roonodeT->holderval = roonodeT->l->id; // Update holder to left child
        token(roonodeT->l, NodeCS, path);
    }
    else {
        if (roonodeT->r == nullptr) {
            cout << "Node " << NodeCS << " not found in the tree!" << endl;
            return;
        }
        roonodeT->holderval = roonodeT->r->id; // Update holder to right child
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

    // Print initial tree structure
    cout << "\nInitial tree structure (Inorder traversal):" << endl;
    TraversalInorder(roonodeT);
    cout << "\nInitial tree structure (ASCII art):" << endl;
    printTreeASCII(roonodeT, path);

    // Input node to enter critical section
    cout << "\nEnter the node for entering CS: ";
    cin >> NodeCS;

    // Process token passing with ASCII art animation
    cout << "\nToken passing animation to node " << NodeCS << ":" << endl;
    token(roonodeT, NodeCS, path);

    // Print final tree structure
    cout << "\nTree structure after token passing (Inorder traversal):" << endl;
    TraversalInorder(roonodeT);
    cout << "\nTree structure after token passing (ASCII art):" << endl;
    printTreeASCII(roonodeT, path);

    // Clean up memory
    destroyTree(roonodeT);

    return 0;
}