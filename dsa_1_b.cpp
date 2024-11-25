#include <iostream>
#include <queue>
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

class Ass1_B {
public:
    Node* root;

    Ass1_B() {
        root = nullptr;
    }

    // Insert a node in the BST
    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            return new Node(data);
        }
        if (data < root->data) {
            root->left = insert(root->left, data);
        } else if (data > root->data) {
            root->right = insert(root->right, data);
        }
        return root;
    }

    // Delete a node from the BST
    Node* deleteNode(Node* root, int data) {
        if (root == nullptr) {
            return nullptr;
        }
        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        } else if (data > root->data) {
            root->right = deleteNode(root->right, data);
        } else {
            // Node found (root->data == data)
            // Case 1: Leaf node
            if (root->left == nullptr && root->right == nullptr) {
                return nullptr;
            }
            // Case 2: One child
            if (root->right == nullptr) {
                return root->left;
            } else if (root->left == nullptr) {
                return root->right;
            }
            // Case 3: Two children
            Node* IS = findInorderSuccessor(root->right);
            root->data = IS->data;
            root->right = deleteNode(root->right, IS->data);
        }
        return root;
    }

    // Find Inorder Successor
    Node* findInorderSuccessor(Node* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    // In-order traversal to display the tree
    void display(Node* root) {
        if (root != nullptr) {
            display(root->left);
            cout << root->data << " ";
            display(root->right);
        }
    }

    // Search for a value in the BST
    bool search(Node* root, int data) {
        if (root == nullptr) {
            return false;
        }
        if (root->data == data) {
            return true;
        }
        if (data < root->data) {
            return search(root->left, data);
        } else {
            return search(root->right, data);
        }
    }

    // Breadth-First Search (BFS) - Level-wise print
    void bfs(Node* root) {
        if (root == nullptr) {
            return;
        }
        queue<Node*> q;
        q.push(root);
        q.push(nullptr); // Level separator

        while (!q.empty()) {
            Node* currNode = q.front();
            q.pop();

            if (currNode == nullptr) {
                cout << endl;
                if (q.empty()) {
                    break;
                } else {
                    q.push(nullptr);
                }
            } else {
                cout << currNode->data << " ";
                if (currNode->left != nullptr) {
                    q.push(currNode->left);
                }
                if (currNode->right != nullptr) {
                    q.push(currNode->right);
                }
            }
        }
    }
};

int main() {
    Ass1_B bst;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a node\n";
        cout << "2. Delete a node\n";
        cout << "3. Display the tree (In-order)\n";
        cout << "4. Search for a node\n";
        cout << "5. BFS (Level-wise print)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Enter the node value to insert: ";
            cin >> value;
            bst.root = bst.insert(bst.root, value);
            cout << "Node inserted." << endl;
            break;
        }
        case 2: {
            int delValue;
            cout << "Enter the node value to delete: ";
            cin >> delValue;
            bst.root = bst.deleteNode(bst.root, delValue);
            cout << "Node deleted." << endl;
            break;
        }
        case 3:
            cout << "Tree (In-order Traversal): ";
            bst.display(bst.root);
            cout << endl;
            break;
        case 4: {
            int searchValue;
            cout << "Enter the node value to search: ";
            cin >> searchValue;
            if (bst.search(bst.root, searchValue)) {
                cout << "Node found in the tree." << endl;
            } else {
                cout << "Node not found in the tree." << endl;
            }
            break;
        }
        case 5:
            cout << "BFS (Level-wise print):\n";
            bst.bfs(bst.root);
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
