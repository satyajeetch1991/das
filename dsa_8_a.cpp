#include <iostream>
#include <vector>
using namespace std;
// Merge function to combine two sorted arrays
void merge(int credits[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            credits[k++] = left[i++];
        } else {
            credits[k++] = right[j++];
        }
    }
    // Copy remaining elements of left array, if any
    while (i < leftSize) {
        credits[k++] = left[i++];
    }
    // Copy remaining elements of right array, if any
    while (j < rightSize) {
        credits[k++] = right[j++];
    }
}
// Merge sort function
void mergeSort(int credits[], int size) {
    if (size < 2) {
        return; // Base case
    }
    int mid = size / 2;
    vector<int> left(mid);
    vector<int> right(size - mid);
    // Fill left and right arrays
    for (int i = 0; i < mid; i++) {
        left[i] = credits[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = credits[i];
    }
    mergeSort(left.data(), mid);  // Sort left half
    mergeSort(right.data(), size - mid); // Sort right half
    merge(credits, left.data(), mid, right.data(), size - mid); // Merge sorted halves
}
int main() {
    cout << "Enter the number of students: ";
    int n;
    cin >> n;
    int* credits = new int[n]; // Dynamic array for credits
    cout << "Enter the credits obtained by each student: ";
    for (int i = 0; i < n; i++) {
        cin >> credits[i];
    }
    mergeSort(credits, n); // Sort credits
    cout << "Sorted credits: ";
    for (int i = 0; i < n; i++) {
        cout << credits[i] << " ";
    }
    cout << endl;
    delete[] credits; // Free dynamic memory
    return 0;
}
// Enter the number of students: 5
// Enter the credits obtained by each student: 15 10 25 5 20
// output 
// Sorted credits: 5 10 15 20 25