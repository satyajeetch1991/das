#include <iostream>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <set>
using namespace std;
// Edge class to represent a flight between two cities with its cost
class Edge {
public:
    string city;
    int cost;
    Edge(string city, int cost) {
        this->city = city;
        this->cost = cost;
    }
};
class Graph {
private:
    map<string, list<Edge>> tickets;  // Map to store cities and their neighbors
public:
    Graph() {}
    // Add a new city
    void addCity(const string& city) {
        if (tickets.find(city) == tickets.end()) {
            tickets[city] = list<Edge>();  // Initialize empty neighbor list
            cout << "City '" << city << "' added." << endl;
        } else {
            cout << "City '" << city << "' already exists." << endl;
        }
    }
    // Add a flight between two cities with the given cost
    void addFlight(const string& cityA, const string& cityB, int cost) {
        if (tickets.find(cityA) == tickets.end() || tickets.find(cityB) == tickets.end()) {
            cout << "Both cities must be added first." << endl;
            return;
        }
        tickets[cityA].push_back(Edge(cityB, cost));  // Add edge from cityA to cityB
        tickets[cityB].push_back(Edge(cityA, cost));  // Add edge from cityB to cityA (undirected graph)
        cout << "Flight path added between '" << cityA << "' and '" << cityB << "' with a cost of " << cost << "." << endl;
    }
    // Check if the graph is connected (i.e., if all cities are reachable)
    bool isConnected() {
        if (tickets.empty()) {
            return true;  // Empty graph is trivially connected
        }
        set<string> visited;
        queue<string> queue;
        string startCity;  // Pick the first city in the map as the starting city
        for (const auto& pair : tickets) {
            startCity = pair.first;
            break;
        }
        // BFS to visit all connected cities
        queue.push(startCity);
        visited.insert(startCity);
        while (!queue.empty()) {
            string currentCity = queue.front();
            queue.pop();
            for (const Edge& neighbor : tickets[currentCity]) {
                if (visited.find(neighbor.city) == visited.end()) {
                    visited.insert(neighbor.city);
                    queue.push(neighbor.city);
                }
            }
        }
        // If all cities are visited, the graph is connected
        return visited.size() == tickets.size();
    }
    // Display the graph's flight paths
    void displayGraph() {
        cout << "Flight paths (Tickets):" << endl;
        for (const auto& pair : tickets) {
            const string& city = pair.first;
            cout << city << " -> ";
            const list<Edge>& edges = pair.second;
            for (const Edge& edge : edges) {
                cout << edge.city << "(" << edge.cost << ") ";
            }
            cout << endl;
        }
    }
};
int main() {
    Graph flightGraph;
    int choice;
    string city, cityA, cityB;
    int cost;
    while (true) {
        cout << "\n--- Flight Network Menu ---" << endl;
        cout << "1. Add City" << endl;
        cout << "2. Add Flight Path" << endl;
        cout << "3. Display Flight Network" << endl;
        cout << "4. Check if Graph is Connected" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Consume newline character after integer input
        switch (choice) {
            case 1:
                // Add a city
                cout << "Enter city name: ";
                getline(cin, city);
                flightGraph.addCity(city);
                break;
            case 2:
                // Add a flight path
                cout << "Enter the source city: ";
                getline(cin, cityA);
                cout << "Enter the destination city: ";
                getline(cin, cityB);
                cout << "Enter the cost of flight (time or fuel): ";
                cin >> cost;
                flightGraph.addFlight(cityA, cityB, cost);
                break;
            case 3:
                // Display the graph
                flightGraph.displayGraph();
                break;
            case 4:
                // Check if the graph is connected
                if (flightGraph.isConnected()) {
                    cout << "The graph is connected. All cities are reachable." << endl;
                } else {
                    cout << "The graph is NOT connected. Some cities are isolated." << endl;
                }
                break;
            case 5:
                // Exit
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}
