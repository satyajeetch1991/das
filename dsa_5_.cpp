#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
class Node {
public:
    int node, weight;
    Node(int node, int weight) {
        this->node = node;
        this->weight = weight;
    }
};
// Comparator for the priority queue to order by weight
struct compareWeight {
    bool operator()(const Node& a, const Node& b) {
        return a.weight > b.weight;
    }
};
class Graph {
public:
    int vertices;
    vector<vector<Node>> adjacencyList;
    Graph(int vertices) {
        this->vertices = vertices;
        adjacencyList.resize(vertices);
    }
    // Add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        adjacencyList[src].push_back(Node(dest, weight));
        adjacencyList[dest].push_back(Node(src, weight)); // For undirected graph
    }
    // Function to perform Dijkstra's algorithm for shortest path
    void shortestPath(int source, int destination) {
        priority_queue<Node, vector<Node>, compareWeight> pq;
        vector<int> distances(vertices, INT_MAX);  // Initialize distances as infinity
        vector<int> parent(vertices, -1);  // Array to store the path
        distances[source] = 0;
        pq.push(Node(source, 0));
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            int u = current.node;
            // If destination is reached
            if (u == destination) {
                cout << "Shortest distance from " << source << " to " 
                << destination << " is: " << distances[destination] << endl;
                printPath(source, destination, parent);
                return;
            }
            // Explore neighbors
            for (const Node& neighbor : adjacencyList[u]) {
                int newDist = distances[u] + neighbor.weight;
                // If a shorter path is found
                if (newDist < distances[neighbor.node]) {
                    distances[neighbor.node] = newDist;
                    parent[neighbor.node] = u;
                    pq.push(Node(neighbor.node, newDist));
                }
            }
        }
        cout << "No path exists from " << source << " to " << destination << endl;
    }
    // Recursive function to print the path from source to destination
    void printPath(int source, int destination, const vector<int>& parent) {
        if (destination == source) {
            cout << source;
            return;
        }
        printPath(source, parent[destination], parent);
        cout << " -> " << destination;
    }
};
int main() {
    int vertices, edgesCount;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    Graph graph(vertices);
    cout << "Enter the number of edges: ";
    cin >> edgesCount;
    cout << "Enter each edge in the format: src dest weight" << endl;
    for (int i = 0; i < edgesCount; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }
    int source, destination;
    cout << "Enter the source vertex: ";
    cin >> source;
    cout << "Enter the destination vertex: ";
    cin >> destination;
    graph.shortestPath(source, destination);
    return 0;
}
// Enter the number of vertices: 5
// Enter the number of edges: 6
// Enter each edge in the format: src dest weight
// 0 1 2
// 0 2 4
// 1 2 1
// 1 3 7
// 2 4 3
// 3 4 1
// Enter the source vertex: 0
// Enter the destination vertex: 4
// output 
// Shortest distance from 0 to 4 is: 8
// Path: 0 -> 1 -> 2 -> 4