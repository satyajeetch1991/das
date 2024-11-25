#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <climits>  // Include this for INT_MIN and INT_MAX
using namespace std;
class User {
public:
    string name;
    string dob;  // format: DD-MM-YYYY
    int comments;

    User(string name, string dob, int comments) {
        this->name = name;
        this->dob = dob;
        this->comments = comments;
    }
};
class Ass3_A {
private:
    map<string, User*> userData; // Maps user names to User objects
    map<string, list<string>> friendsNetwork; // Maps user names to lists of friends
public:
    // Add a new user
    void addUser(string name, string dob, int comments) {
        User* newUser = new User(name, dob, comments);
        userData[name] = newUser;
        friendsNetwork[name] = list<string>();  // Initialize empty friend list
    }
    // Add a friendship (bidirectional)
    void addFriendship(string user1, string user2) {
        if (friendsNetwork.find(user1) == friendsNetwork.end() || friendsNetwork.find(user2) == friendsNetwork.end()) {
            cout << "Error: One or both users do not exist. Please add the users first." << endl;
            return;
        }
        friendsNetwork[user1].push_back(user2);
        friendsNetwork[user2].push_back(user1);
    }
    // 1. Find the user with maximum friends
    void findMaxFriends() {
        string maxUser;
        int maxFriends = 0;
        for (auto& entry : friendsNetwork) {
            int friendCount = entry.second.size();
            if (friendCount > maxFriends) {
                maxFriends = friendCount;
                maxUser = entry.first;
            }
        }
        if (!maxUser.empty()) {
            cout << "User with maximum friends: " << maxUser << " (Friends: " << maxFriends << ")" << endl;
        }
    }
    // 2. Find user with maximum and minimum comments
    void findMaxAndMinComments() {
        if (userData.empty()) return;
        string maxCommentUser, minCommentUser;
        int maxComments = INT_MIN;
        int minComments = INT_MAX;
        for (auto& entry : userData) {
            User* user = entry.second;
            if (user->comments > maxComments) {
                maxComments = user->comments;
                maxCommentUser = user->name;
            }
            if (user->comments < minComments) {
                minComments = user->comments;
                minCommentUser = user->name;
            }
        }
        cout << "User with maximum comments: " << maxCommentUser << " (Comments: " << maxComments << ")" << endl;
        cout << "User with minimum comments: " << minCommentUser << " (Comments: " << minComments << ")" << endl;
    }
    // 3. Find users having birthday in the current month
    void findBirthdayUsers() {
        time_t t = time(0);   // get time now
        tm* now = localtime(&t);
        int currentMonth = now->tm_mon + 1; // Get current month (1-based index)
        cout << "Users having birthday this month:" << endl;
        for (auto& entry : userData) {
            string dob = entry.second->dob;
            int birthMonth = stoi(dob.substr(3, 2));  // Extract month from DOB

            if (birthMonth == currentMonth) {
                cout << entry.second->name << " (Birthday: " << entry.second->dob << ")" << endl;
            }
        }
    }
    // Perform DFS traversal
    void DFS(string startUser) {
        if (friendsNetwork.find(startUser) == friendsNetwork.end()) {
            cout << "Error: User does not exist." << endl;
            return;
        }
        set<string> visited;
        stack<string> s;
        s.push(startUser);
        cout << "DFS Traversal: ";
        while (!s.empty()) {
            string currentUser = s.top();
            s.pop();

            if (visited.find(currentUser) == visited.end()) {
                cout << currentUser << " ";
                visited.insert(currentUser);

                // Add friends to the stack
                for (auto it = friendsNetwork[currentUser].rbegin(); it != friendsNetwork[currentUser].rend(); ++it) {
                    if (visited.find(*it) == visited.end()) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << endl;
    }
    // Perform BFS traversal
    void BFS(string startUser) {
        if (friendsNetwork.find(startUser) == friendsNetwork.end()) {
            cout << "Error: User does not exist." << endl;
            return;
        }
        set<string> visited;
        queue<string> q;
        q.push(startUser);
        cout << "BFS Traversal: ";
        while (!q.empty()) {
            string currentUser = q.front();
            q.pop();
            if (visited.find(currentUser) == visited.end()) {
                cout << currentUser << " ";
                visited.insert(currentUser);
                // Add friends to the queue
                for (auto& friendUser : friendsNetwork[currentUser]) {
                    if (visited.find(friendUser) == visited.end()) {
                        q.push(friendUser);
                    }
                }
            }
        }
        cout << endl;
    }
    // Menu-driven program
    void displayMenu() {
        int choice;
        do {
            cout << "\n--- Social Network Menu ---" << endl;
            cout << "1. Add User" << endl;
            cout << "2. Add Friendship" << endl;
            cout << "3. Find User with Maximum Friends" << endl;
            cout << "4. Find User with Maximum and Minimum Comments" << endl;
            cout << "5. Find Users Having Birthday in This Month" << endl;
            cout << "6. DFS Traversal" << endl;
            cout << "7. BFS Traversal" << endl;
            cout << "8. Exit" << endl;
            cout << "Enter your choice (1-8): ";
            cin >> choice;
            cin.ignore();  // Consume newline character

            switch (choice) {
                case 1: {
                    string name, dob;
                    int comments;
                    cout << "Enter user name: ";
                    getline(cin, name);
                    cout << "Enter date of birth (DD-MM-YYYY): ";
                    getline(cin, dob);
                    cout << "Enter number of comments: ";
                    cin >> comments;
                    addUser(name, dob, comments);
                    break;
                }
                case 2: {
                    string user1, user2;
                    cout << "Enter first user name: ";
                    getline(cin, user1);
                    cout << "Enter second user name: ";
                    getline(cin, user2);
                    addFriendship(user1, user2);
                    break;
                }
                case 3:
                    findMaxFriends();
                    break;
                case 4:
                    findMaxAndMinComments();
                    break;
                case 5:
                    findBirthdayUsers();
                    break;
                case 6: {
                    string dfsUser;
                    cout << "Enter starting user for DFS: ";
                    getline(cin, dfsUser);
                    DFS(dfsUser);
                    break;
                }
                case 7: {
                    string bfsUser;
                    cout << "Enter starting user for BFS: ";
                    getline(cin, bfsUser);
                    BFS(bfsUser);
                    break;
                }
                case 8:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please choose again." << endl;
            }
        } while (choice != 8);
    }
};
int main() {
    Ass3_A socialNetwork;

    // Display the menu
    socialNetwork.displayMenu();

    return 0;
}
