#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Student {
public:
    string name;
    int credits;
    Student(string name, int credits) {
        this->name = name;
        this->credits = credits;
    }
};
// Function to swap two students
void swap(Student& a, Student& b) {
    Student temp = a;
    a = b;
    b = temp;
}
// Partition function for quicksort
int partition(vector<Student>& students, int low, int high) {
    int pivot = students[high].credits; // Taking the last student's credits as pivot
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (students[j].credits > pivot) { // For descending order
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}
// Quicksort function
void quickSort(vector<Student>& students, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(students, low, high);
        quickSort(students, low, pivotIndex - 1);
        quickSort(students, pivotIndex + 1, high);
    }
}
int main() {
    cout << "Enter the number of students: ";
    int n;
    cin >> n;
    cin.ignore(); // Ignore the newline character after the number input
    vector<Student> students; // Vector to hold Student objects
    for (int i = 0; i < n; i++) {
        cout << "Enter name of student " << (i + 1) << ": ";
        string name;
        getline(cin, name); // Read full name including spaces
        cout << "Enter credits for " << name << ": ";
        int credits;
        cin >> credits;
        cin.ignore(); // Ignore the newline character after the credits input
        students.emplace_back(name, credits); // Add new Student to vector
    }
    quickSort(students, 0, n - 1); // Sort students by credits
    cout << "Top 3 students based on credits:\n";
    for (int i = 0; i < min(3, n); i++) {
        cout << (i + 1) << ". " << students[i].name << " - " << students[i].credits << " credits\n";
    }
    return 0;
}
// Enter the number of students: 5
// Enter name of student 1: Alice
// Enter credits for Alice: 85
// Enter name of student 2: Bob
// Enter credits for Bob: 92
// Enter name of student 3: Charlie
// Enter credits for Charlie: 78
// Enter name of student 4: Diana
// Enter credits for Diana: 95
// Enter name of student 5: Eva
// Enter credits for Eva: 88
// output 
// Top 3 students based on credits:
// 1. Diana - 95 credits
// 2. Bob - 92 credits
// 3. Eva - 88 credits