#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

int findFarthestPage(const vector<int>& pages, const unordered_map<int, int>& pageIndices, int currentIndex, int n) {
    int farthestIndex = -1;
    int farthestDistance = numeric_limits<int>::min();

    for (const auto& entry : pageIndices) {
        int nextPage = entry.first;
        int nextIndex = entry.second;
        
        int distance = n;
        for (int i = currentIndex + 1; i < n; ++i) {
            if (pages[i] == nextPage) {
                distance = i - currentIndex;
                break;
            }
        }

        if (distance > farthestDistance) {
            farthestDistance = distance;
            farthestIndex = nextIndex;
        }
    }

    return farthestIndex;
}

void shortestPageReplacement(const vector<int>& pages, int capacity) {
    int n = pages.size();
    unordered_map<int, int> pageIndices;
    vector<int> memory;
    int pageFaults = 0;

    for (int i = 0; i < n; ++i) {
        if (pageIndices.find(pages[i]) != pageIndices.end()) {
            cout << "Page " << pages[i] << " is already in memory." << endl;
        } else {
            ++pageFaults;

            if (memory.size() < capacity) {
                memory.push_back(pages[i]);
                pageIndices[pages[i]] = memory.size() - 1;
            } else {
                int index = findFarthestPage(pages, pageIndices, i, n);
                int replacedPage = memory[index];
                cout << "Page " << replacedPage << " is replaced by Page " << pages[i] << "." << endl;
                memory[index] = pages[i];
                pageIndices.erase(replacedPage);
                pageIndices[pages[i]] = index;
            }
        }
    }

    cout << "Total Page Faults: " << pageFaults << endl;
}

int main() {
    vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

    int capacity = 3;
    shortestPageReplacement(pages, capacity);

    return 0;
}
