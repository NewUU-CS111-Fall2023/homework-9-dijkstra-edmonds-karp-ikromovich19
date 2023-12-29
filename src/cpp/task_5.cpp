#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int, int>>> graph(n);  
    for (const auto& flight : flights) {
        graph[flight[0]].push_back({flight[1], flight[2]});
    }

    vector<int> distances(n, INT_MAX);
    distances[src] = 0;  
    queue<pair<int, int>> q;  
    q.push({src, 0});  

    while (!q.empty()) {
        int city = q.front().first;
        int stops = q.front().second;
        q.pop();

        if (stops > k) {
            continue;  
        }

        for (const auto& neighbor : graph[city]) {
            int neighborCity = neighbor.first;
            int cost = neighbor.second;

            int newCost = distances[city] + cost;
            if (newCost < distances[neighborCity]) {
                distances[neighborCity] = newCost;
                q.push({neighborCity, stops + 1});  
            }
        }
    }

    return distances[dst] == INT_MAX ? -1 : distances[dst];
}

int main() {
    int n = 3;
    vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    int src = 0, dst = 2, k = 1;

    int cheapestPrice = findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest price: " << cheapestPrice << endl;  

    return 0;
}
