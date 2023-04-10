#include <iostream>
#include <queue>

using namespace std;

struct Job {
    int id;
    int arrivalTime;
    int runTime;
    int waitingTime;
    int priority;
};

class ComparePriority {
public:
    bool operator()(Job const& j1, Job const& j2) {
        return j1.priority > j2.priority;
    }
};

int main() {
    priority_queue<Job, vector<Job>, ComparePriority> jobQueue;
    int numJobs;
    cout << "Enter the number of jobs: ";
    cin >> numJobs;
    for (int i = 0; i < numJobs; i++) {
        Job job;
        job.id = i + 1;
        cout << "Enter the arrival time and run time for job " << job.id << ": ";
        cin >> job.arrivalTime >> job.runTime;
        job.waitingTime = 0;
        job.priority = 1;
        jobQueue.push(job);
    }
    int currentTime = 0;
    cout << "Gantt chart:\n";
    while (!jobQueue.empty()) {
        Job currentJob = jobQueue.top();
        jobQueue.pop();
        cout << "Job " << currentJob.id << " (" << currentJob.priority << ") ";
        currentJob.waitingTime += currentTime - currentJob.arrivalTime;
        currentTime += currentJob.runTime;
        cout << "[" << currentTime << "]" << endl;
        while (!jobQueue.empty() && jobQueue.top().arrivalTime <= currentTime) {
            Job waitingJob = jobQueue.top();
            jobQueue.pop();
            waitingJob.waitingTime += currentTime - waitingJob.arrivalTime;
            waitingJob.priority = 1 + waitingJob.waitingTime / waitingJob.runTime;
            jobQueue.push(waitingJob);
        }
    }
    int totalWaitingTime = 0;
    while (!jobQueue.empty()) {
        Job job = jobQueue.top();
        jobQueue.pop();
        job.waitingTime += currentTime - job.arrivalTime;
        totalWaitingTime += job.waitingTime;
    }
    double avgWaitingTime = (double)totalWaitingTime / numJobs;
    cout << "Average waiting time: " << avgWaitingTime << endl;
    return 0;
}
