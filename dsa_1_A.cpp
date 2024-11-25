#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;

    Node(int item) {
        data = item;
        left = right = nullptr;
    }
};
class Ass1_A {
public:
    Node* root;
    Ass1_A() {
        root = nullptr;
    }
    // Insert a node into the binary tree
    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            node = new Node(data);
            return node;
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        }
        return node;
    }
    // Display the tree (In-order traversal)
    void display(Node* node) {
        if (node != nullptr) {
            display(node->left);
            cout << node->data << " ";
            display(node->right);
        }
    }
    // Find the depth of the tree
    int findDepth(Node* node) {
        if (node == nullptr) {
            return 0;
        } else {
            int leftDepth = findDepth(node->left);
            int rightDepth = findDepth(node->right);
            return max(leftDepth, rightDepth) + 1;
        }
    }
    // Display the leaf nodes
    void displayLeafNodes(Node* node) {
        if (node == nullptr) {
            return;
        }
        if (node->left == nullptr && node->right == nullptr) {
            cout << node->data << " ";
        }
        displayLeafNodes(node->left);
        displayLeafNodes(node->right);
    }
    // Create a copy of the tree
    Node* createCopy(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Node* newNode = new Node(node->data);
        newNode->left = createCopy(node->left);
        newNode->right = createCopy(node->right);
        return newNode;
    }
};
int main() {
    Ass1_A tree;
    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Insert a node" << endl;
        cout << "2. Display the tree (In-order)" << endl;
        cout << "3. Find depth of the tree" << endl;
        cout << "4. Display leaf nodes" << endl;
        cout << "5. Create a copy of the tree and display" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            int value;
            cout << "Enter the node value to insert: ";
            cin >> value;
            tree.root = tree.insert(tree.root, value);
            cout << "Node inserted." << endl;
            break;
        }
        case 2:
            cout << "Tree (In-order Traversal): ";
            tree.display(tree.root);
            cout << endl;
            break;
        case 3:
            cout << "Depth of tree: " << tree.findDepth(tree.root) << endl;
            break;
        case 4:
            cout << "Leaf nodes: ";
            tree.displayLeafNodes(tree.root);
            cout << endl;
            break;
        case 5: {
            Node* copy = tree.createCopy(tree.root);
            cout << "Copied Tree (In-order Traversal): ";
            tree.display(copy);
            cout << endl;
            break;
        }
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);
    return 0;
}
