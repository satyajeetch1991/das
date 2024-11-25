#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
// Pair class to represent a node and the weight of an edge
class Pair {
public:
    int node, weight;
    Pair(int node, int weight) {
        this->node = node;
        this->weight = weight;
    }
};
// Comparator for the priority queue to order by weight
struct compareWeight {
    bool operator()(const Pair& a, const Pair& b) {
        return a.weight > b.weight;
    }
};
class Graph {
private:
    int V;  // Number of vertices
    vector<vector<Pair>> adjList;  // Adjacency list
public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }
    // Add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back(Pair(dest, weight));
        adjList[dest].push_back(Pair(src, weight));
    }
    // Function to perform Prim's MST algorithm
    void primMST() {
        vector<int> key(V, INT_MAX);  // Key values used to pick minimum weight edge
        vector<bool> visited(V, false);  // To keep track of vertices included in MST
        vector<int> parent(V, -1);  // To store the MST
        priority_queue<Pair, vector<Pair>, compareWeight> pq;  // Min-heap priority queue
        key[0] = 0;  // Start from the first node
        pq.push(Pair(0, 0));  // Insert the first node with a weight of 0
        while (!pq.empty()) {
            int u = pq.top().node;  // Extract the node with the minimum key value
            pq.pop();
            visited[u] = true;  // Include u in MST
            // Traverse all adjacent vertices of u
            for (const Pair& neighbor : adjList[u]) {
                int v = neighbor.node;
                int weight = neighbor.weight;
                // If v is not in MST and the weight of u-v is smaller than the current key of v
                if (!visited[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push(Pair(v, key[v]));  // Add v to the priority queue
                    parent[v] = u;  // Update parent of v
                }
            }
        }
        printMST(parent, key);
    }
    // Function to print the MST and its total weight
    void printMST(const vector<int>& parent, const vector<int>& key) {
        cout << "MST Graph -\n";
        cout << "Edge \tWeight\n";
        int totalWeight = 0;
        for (int i = 1; i < V; ++i) {
            cout << parent[i] << " - " << i << "\t" << key[i] << "\n";
            totalWeight += key[i];
        }
        cout << "Total weight of MST: " << totalWeight << endl;
    }
};
int main() {
    int nodes, edgesCount;
    cout << "Enter the number of nodes: ";
    cin >> nodes;
    Graph graph(nodes);
    cout << "Enter the number of edges: ";
    cin >> edgesCount;
    cout << "Enter each edge in the format: src dest weight\n";
    for (int i = 0; i < edgesCount; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }
    graph.primMST();
    return 0;
}
// Enter the number of nodes: 5
// Enter the number of edges: 7
// Enter each edge in the format: src dest weight
// 0 1 2
// 0 3 6
// 1 3 8
// 1 2 3
// 1 4 5
// 2 4 7
// 3 4 9
// output
// MST Graph -
// Edge    Weight
// 0 - 1   2
// 1 - 2   3
// 1 - 4   5
// 0 - 3   6
// Total weight of MST: 16