#include <iostream>
#include <stack>
#include <string>
using namespace std;
class Node {
public:
    string data;
    Node *left, *right;

    Node(string data) {
        this->data = data;
        left = right = nullptr;
    }
};
class Ass2_a {
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
    // In-order traversal of the expression tree
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
};
int main() {
    Ass2_a tree;
    string postfix;
    cout << "Enter postfix expression: ";
    getline(cin, postfix); // Example postfix expression -> ab+cde+**
    Node* root = tree.constructTree(postfix);
    cout << "In-order Traversal of the Expression Tree: ";
    tree.inOrderTraversal(root);
    cout << endl;
    return 0;
}
