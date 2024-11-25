#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main() {
    int n;
    // Max-heap to store maximum marks (inverted priority queue)
    priority_queue<int> maxHeap;
    // Min-heap to store minimum marks
    priority_queue<int, vector<int>, greater<int>> minHeap;
    cout << "Enter the number of students: ";
    cin >> n;
    cout << "Enter the marks obtained by each student:" << endl;
    for (int i = 0; i < n; i++) {
        int marks;
        cin >> marks;
        maxHeap.push(marks);  // Add marks to max-heap
        minHeap.push(marks);  // Add marks to min-heap
    }
    int maxMarks = maxHeap.top();  // Top of max-heap is the maximum
    int minMarks = minHeap.top();  // Top of min-heap is the minimum
    cout << "Maximum marks obtained: " << maxMarks << endl;
    cout << "Minimum marks obtained: " << minMarks << endl;
    return 0;
}
// Enter the number of students: 5
// Enter the marks obtained by each student:
// 85
// 92
// 75
// 64
// 99
// Maximum marks obtained: 99
// Minimum marks obtained: 64