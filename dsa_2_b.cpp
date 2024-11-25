#include <iostream>
#include <stack>
#include <string>
using namespace std;
class Node {
public:
    string data;
    Node* left;
    Node* right;
    Node(string data) {
        this->data = data;
        left = right = nullptr;
    }
};
class Ass2_B {
public:
    // Construct an Expression Tree from postfix expression
    Node* constructTree(string postfix) {
        stack<Node*> s;
        for (int i = 0; i < postfix.length(); i++) {
            char ch = postfix[i];
            // If the character is an operand, create a new node and push to stack
            if (isalnum(ch)) { // isalnum checks if the character is a letter or digit
                s.push(new Node(string(1, ch))); // Convert char to string
            }
            // If the character is an operator, pop two nodes and create a new node for the operator
            else {
                Node* operatorNode = new Node(string(1, ch));
                operatorNode->right = s.top();
                s.pop();
                operatorNode->left = s.top();
                s.pop();
                s.push(operatorNode);
            }
        }
        return s.top();
    }
    // In-order traversal -> Left - Root - Right
    void inOrderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }
        stack<Node*> s;
        Node* current = root;
        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();
            cout << current->data << " ";
            current = current->right;
        }
    }
    // Non-recursive pre-order traversal -> Root - Left - Right
    void preOrderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }
        stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            Node* current = s.top();
            s.pop();
            cout << current->data << " ";

            if (current->right != nullptr) {
                s.push(current->right);
            }
            if (current->left != nullptr) {
                s.push(current->left);
            }
        }
    }
    // Non-recursive post-order traversal -> Left - Right - Root
    void postOrderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }
        stack<Node*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            Node* current = s1.top();
            s1.pop();
            s2.push(current);
            if (current->left != nullptr) {
                s1.push(current->left);
            }
            if (current->right != nullptr) {
                s1.push(current->right);
            }
        }
        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
    }
    // Display menu for traversal options
    void displayMenu(Node* root) {
        int choice;
        do {
            cout << "\n--- Expression Tree Traversal Menu ---" << endl;
            cout << "1. In-order Traversal" << endl;
            cout << "2. Pre-order Traversal" << endl;
            cout << "3. Post-order Traversal" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice (1-4): ";
            cin >> choice;
            switch (choice) {
            case 1:
                cout << "\nIn-order Traversal: ";
                inOrderTraversal(root);
                cout << endl;
                break;
            case 2:
                cout << "\nPre-order Traversal: ";
                preOrderTraversal(root);
                cout << endl;
                break;
            case 3:
                cout << "\nPost-order Traversal: ";
                postOrderTraversal(root);
                cout << endl;
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please choose again." << endl;
            }
        } while (choice != 4);
    }
};
int main() {
    Ass2_B tree;
    cout << "Enter postfix Expression: ";
    string postfix;
    getline(cin, postfix); // Example postfix expression -> ab+cde+**
    Node* root = tree.constructTree(postfix);
    tree.displayMenu(root);
    return 0;
}
