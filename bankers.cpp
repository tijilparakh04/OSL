#include <iostream>
#include <vector>

using namespace std;

bool isSafe(const vector<vector<int>>& need, const vector<int>& available, const vector<vector<int>>& allocation, vector<int>& work, vector<bool>& finished, vector<int>& safeSequence) {
    int n = allocation.size();
    int m = allocation[0].size();

    for (int i = 0; i < n; ++i) {
        if (!finished[i]) {
            bool canAllocate = true;
            for (int j = 0; j < m; ++j) {
                if (need[i][j] > work[j]) {
                    canAllocate = false;
                    break;
                }
            }
            if (canAllocate) {
                for (int j = 0; j < m; ++j) {
                    work[j] += allocation[i][j];
                }
                finished[i] = true;
                safeSequence.push_back(i);
                if (isSafe(need, available, allocation, work, finished, safeSequence))
                    return true;
                safeSequence.pop_back();
                for (int j = 0; j < m; ++j) {
                    work[j] -= allocation[i][j];
                }
                finished[i] = false;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!finished[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n; 
    int m; 

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    vector<vector<int>> max(n, vector<int>(m));
    cout << "Enter the maximum resources required for each process:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < m; ++j) {
            cin >> max[i][j];
        }
    }

    vector<vector<int>> allocation(n, vector<int>(m));
    cout << "Enter the allocated resources for each process:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < m; ++j) {
            cin >> allocation[i][j];
        }
    }

    vector<int> available(m);
    cout << "Enter the available resources:" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> available[i];
    }

    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    vector<int> work = available;
    vector<bool> finished(n, false);
    vector<int> safeSequence;

    if (isSafe(need, available, allocation, work, finished, safeSequence)) {
        cout << "System is in a safe state." << endl;
        cout << "Safe sequence: ";
        for (int i = 0; i < safeSequence.size(); ++i) {
            cout << safeSequence[i];
            if (i != safeSequence.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;

        cout << "Need Matrix:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "Process " << i << ": ";
            for (int j = 0; j < m; ++j) {
                cout << need[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "System is in an unsafe state." << endl;
    }

    return 0;
}
