#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Job {
    int id;        // Job ID
    int deadline;  // Job deadline
    int profit;    // Job profit
};
// Function to get job input from the user
vector<Job> getJobInput() {
    cout << "Enter the number of jobs: ";
    int n;
    cin >> n;
    vector<Job> jobs(n);    
    for (int i = 0; i < n; i++) {
        cout << "Enter deadline and profit for job " << (i + 1) << ": ";
        cin >> jobs[i].deadline >> jobs[i].profit;
        jobs[i].id = i + 1; // Assign job ID
    }
    return jobs;
}
// Function to select jobs based on profit and deadline
vector<int> selectJobs(vector<Job>& jobs) {
    // Sort jobs in decreasing order of profit
    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.profit > b.profit;
    });
    vector<int> seq; // To store selected job IDs
    int time = 0;    // To keep track of the current time
    for (const auto& curr : jobs) {
        if (curr.deadline > time) {
            seq.push_back(curr.id);
            time++; // Increment time as a job is scheduled
        }
    }
    return seq;
}
int main() {
    vector<Job> jobs = getJobInput();
    vector<int> selectedJobs = selectJobs(jobs);
    // Print the result
    cout << "Max jobs: " << selectedJobs.size() << endl;
    cout << "Selected Job IDs: ";
    for (int id : selectedJobs) {
        cout << id << " ";
    }
    cout << endl;
    return 0;
}

// Enter the number of jobs: 4
// Enter deadline and profit for job 1: 4 20
// Enter deadline and profit for job 2: 1 10
// Enter deadline and profit for job 3: 2 40
// Enter deadline and profit for job 4: 3 30
// output 
// Max jobs: 3
// Selected Job IDs: 3 4 1