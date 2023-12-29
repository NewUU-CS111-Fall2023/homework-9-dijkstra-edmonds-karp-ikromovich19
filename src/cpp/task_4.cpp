#include <iostream>
#include <vector>
#include <queue>

using namespace std;


struct Edge {
    int source, target, weight;
};

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
   
    vector<vector<pair<int, int>>> graph(n + 1);  
    for (const auto& edge : times) {
        graph[edge[0]].push_back({edge[1], edge[2]});
    }

    
    vector<int> distances(n + 1, INT_MAX);
    distances[k] = 0;

   
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});  

   
    while (!pq.empty()) {
        auto [currentDistance, currentNode] = pq.top();
        pq.pop();

        if (currentDistance > distances[currentNode]) {
            continue;  
        }

        for (const auto& neighbor : graph[currentNode]) {
            int neighborNode = neighbor.first;
            int newDistance = currentDistance + neighbor.second;

            if (newDistance < distances[neighborNode]) {
                distances[neighborNode] = newDistance;
                pq.push({newDistance, neighborNode});
            }
        }
    }

    int maxDistance = *max_element(distances.begin() + 1, distances.end());

    return maxDistance == INT_MAX ? -1 : maxDistance;  

int main() {
    vector<vector<int>> times1 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n1 = 4, k1 = 2;
    cout << networkDelayTime(times1, n1, k1) << endl;  

    vector<vector<int>> times2 = {{1, 2, 1}};
    int n2 = 2, k2 = 1;
    cout << networkDelayTime(times2, n2, k2) << endl;  

    vector<vector<int>> times3 = {{1, 2, 1}};
    int n3 = 2, k3 = 2;
    cout << networkDelayTime(times3, n3, k3) << endl;  

    return 0;
}
