#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;

class Process {
public:
    int n;
    int burst_time;
    int arrival_time;
    int waiting_time = 0;
    int turnaround_time = 0;
    int completion_time = 0;
    int name;
    bool completed = false;
    bool arrived = false;
};

queue<Process> ready;

bool compareArrival(Process p1, Process p2) {
    return p1.arrival_time < p2.arrival_time;
}

bool compareBurst(Process p1, Process p2) {
    return p1.burst_time < p2.burst_time;
}

bool compareCompletion(Process p1, Process p2) {
    return p1.completion_time < p2.completion_time;
}


void setarrival(Process a[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        cout << "Enter the arrival time of process number " << i + 1 << endl;
        cin >> a[i].arrival_time;
    }
}

void setburst(Process a[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        a[i].name = i + 1;
        cout << "Enter the burst time of process number " << i + 1 << endl;
        cin >> a[i].burst_time;
    }
}

void run(Process a[], int n) {
    int current_time = 0;
    while (true) {
        vector<Process> arrived_processes;
        for (int j = 0; j < n; j++) {
            if (a[j].arrival_time <= current_time && a[j].completed == false && a[j].arrived == false) {
                arrived_processes.push_back(a[j]);
            }
        }
        if(!arrived_processes.empty())
        {
            sort(arrived_processes.begin(), arrived_processes.end(), compareBurst);
            ready.push(arrived_processes[0]);
            for (int i = 0; i < n; i++) {
            if (a[i].name == arrived_processes[0].name) {
                a[i].arrived = true;
                break;
            }
        }
        }        
        
        arrived_processes.clear();
        if (!ready.empty()) {
            Process current_process = ready.front();
            ready.pop();
            current_time += current_process.burst_time;
            current_process.completion_time = current_time;
            current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
            current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;
            current_process.completed = true;
            for (int i = 0; i < n; i++) {
                if (a[i].name == current_process.name) {
                    a[i] = current_process;
                    break;
                }
            }
        } else {
            current_time++;
        }
        bool all_completed = true;
        for (int i = 0; i < n; i++) {
            if (!a[i].completed) {
                all_completed = false;
                break;
            }
        }
        if (all_completed) {
            break;
        }
    }
}

void avgtime(Process a[], int n) {
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += a[i].waiting_time;
        avg_turnaround_time += a[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

void display(Process a[], int n) {
    cout << setw(15) << "Process" << setw(15) << "Burst Time" << setw(15) << "Arrival Time" << setw(15) << "Waiting Time" << setw(20) << "Turnaround Time" << setw(20) << "Completion Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(15) << a[i].name << setw(15) << a[i].burst_time << setw(15) << a[i].arrival_time << setw(15) << a[i].waiting_time << setw(20) << a[i].turnaround_time << setw(20) << a[i].completion_time << endl;
    }
}


void ganttchart(Process a[], int n)
{
    sort(a, a + n, compareCompletion);
    int i;
    cout << "|";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << a[i].name;
        for (int j = 0; j < a[i].burst_time - 1; j++)
        {
            cout << " ";
        }
        if (i < n - 1)
        {
            cout << "|";
        }
    }

    cout << "|" << endl;
    cout << a[0].arrival_time;
    for (int i = 0; i < n; i++)
    {
        cout<<" ";
        if(a[i].completion_time>9)
        {
            for (int j = 0; j < a[i].burst_time-1; j++)
            {
                cout << " ";
            }
        }
        else
        {
            for (int j = 0; j < a[i].burst_time; j++)
            {
                cout << " ";
            }
        }
        
        if (i <= n - 1)
        {
            cout << a[i].completion_time;
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: " << endl;
    cin >> n;
    Process *a = new Process[n];

    setburst(a, n);
    setarrival(a, n);
    sort(a, a + n, compareArrival);
    run(a, n);
    display(a, n);
    avgtime(a, n);
    ganttchart(a, n);
    delete[] a; // Deallocate memory

    return 0;
}
