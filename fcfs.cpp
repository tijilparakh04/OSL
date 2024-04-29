#include <iostream>
#include <iomanip>
using namespace std;

class Process
{
public:
    int n;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int name;
};

void swap(Process *p, Process *q)
{
    Process temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

void bubble(Process a[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j].arrival_time > a[j + 1].arrival_time)
            {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

void setarrival(Process a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        cout << "Enter the arrival time of process number " << i + 1 << endl;
        cin >> a[i].arrival_time;
    }
}

void setburst(Process a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        a[i].name = i + 1;
        cout << "Enter the burst time of process number " << i + 1 << endl;
        cin >> a[i].burst_time;
    }
}

void calculate_completion(Process a[], int n)
{
    int i;
    a[0].completion_time = a[0].arrival_time + a[0].burst_time;
    for (i = 1; i < n; i++)
    {
        a[i].completion_time = (a[i].burst_time + a[i - 1].completion_time);
    }
}

void calculate_waiting(Process a[], int n)
{
    int i;
    a[0].waiting_time = 0;
    for (i = 1; i < n; i++)
    {
        if (a[i].arrival_time > a[i - 1].completion_time)
        {
            a[i].waiting_time = 0;
        }
        else
        {
            a[i].waiting_time = a[i - 1].completion_time - a[i].arrival_time;
        }
    }
}

void calculate_turnaround(Process a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        a[i].turnaround_time = a[i].completion_time - a[i].arrival_time;
    }
}

void calculate_avg(Process a[], int n)
{
    float avg_waiting_time, avg_turnaround_time;
    int i;
    float sumwaiting = 0;
    float sumturnaround = 0;
    for (i = 0; i < n; i++)
    {
        sumwaiting += a[i].waiting_time;
        sumturnaround += a[i].turnaround_time;
    }
    avg_waiting_time = sumwaiting / n;
    avg_turnaround_time = sumturnaround / n;
    cout << "Average waiting time is : " << avg_waiting_time << endl;
    cout << "Average turnaround time is : " << avg_turnaround_time << endl;
}

void display(Process a[], int n)
{
    int i;
    cout << setw(15) << "Process " << setw(15) << "Burst Time" << setw(15) << "Arrival Time" << setw(15) << "Waiting Time" << setw(20) << "Turnaround Time" << setw(20) << "Completion Time" << endl;
    for (i = 0; i < n; i++)
    {
        cout << setw(15) << a[i].name << setw(15) << a[i].burst_time << setw(15) << a[i].arrival_time << setw(15) << a[i].waiting_time << setw(20) << a[i].turnaround_time << setw(20) << a[i].completion_time << endl;
    }
}

void ganttchart(Process a[], int n)
{
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
        for (int j = 0; j < a[i].burst_time; j++)
        {
            cout << " ";
        }
        if (i < n - 1)
        {
            cout << a[i].completion_time;
        }
    }
}

main()
{
    int n;
    cout << "Enter the number of processes: " << endl;
    cin >> n;
    Process a[n];

    setburst(a, n);
    setarrival(a, n);
    bubble(a, n);
    calculate_completion(a, n);
    calculate_waiting(a, n);
    calculate_turnaround(a, n);
    display(a, n);
    calculate_avg(a, n);
    ganttchart(a, n);
}