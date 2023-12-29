#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int findShortestPathWithFuel(int n, vector<vector<int>>& flights, int src, int dst, int k, int f) {
    vector<vector<pair<int, int>>> graph(n);  
    for (const auto& flight : flights) {
        graph[flight[0]].push_back({flight[1], {flight[2], flight[3]}});
    }

    vector<int> distances(n, INT_MAX);
    distances[src] = 0;  

    queue<pair<int, int>> q;  
    q.push({src, f});  

    while (!q.empty()) {
        int city = q.front().first;
        int remainingFuel = q.front().second;
        q.pop();

        if (city == dst) {
            return distances[city];
        }

        for (const auto& neighbor : graph[city]) {
            int neighborCity = neighbor.first;
            int distance = neighbor.second.first;
            int hasARS = neighbor.second.second;

            if (remainingFuel >= distance) {  
                int newRemainingFuel = hasARS ? f : remainingFuel - distance;
                int newDistance = distances[city] + distance;

                if (newDistance < distances[neighborCity]) {
                    distances[neighborCity] = newDistance;
                    q.push({neighborCity, newRemainingFuel});
                }
            }
        }
    }

    return -1;  
}

int main() {
    int n = 4;
    vector<vector<int>> flights = {{0, 1, 100, 0}, {1, 2, 600, 1}, {2, 0, 100, 1}, {1, 3, 600, 0}, {2, 3, 200, 0}};
    int src = 0, dst = 3, k = 2, f = 600;

    int shortestDistance = findShortestPathWithFuel(n, flights, src, dst, k, f);
    cout << "Shortest distance: " << shortestDistance << endl;  

    return 0;
}
