#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int from, to, capacity, flow;
};

int getMaxFlow(vector<vector<Edge>>& graph, int source, int sink) {
    int flow = 0;

    while (true) {
        queue<int> q;
        q.push(source);

        vector<int> pred(graph.size(), -1);
        pred[source] = -2;

        while (!q.empty() && pred[sink] == -1) {
            int cur = q.front();
            q.pop();

            for (const auto& edge : graph[cur]) {
                int next = edge.to;
                if (pred[next] == -1 && edge.flow < edge.capacity) {
                    pred[next] = cur;
                    q.push(next);
                }
            }
        }

        if (pred[sink] == -1) {
            break;
        }

        int augmentFlow = INT_MAX;
        int u = sink;
        while (u != source) {
            int v = pred[u];
            for (auto& edge : graph[v]) {
                if (edge.to == u) {
                    augmentFlow = min(augmentFlow, edge.capacity - edge.flow);
                    break;
                }
            }
            u = v;
        }

        u = sink;
        while (u != source) {
            int v = pred[u];
            for (auto& edge : graph[v]) {
                if (edge.to == u) {
                    edge.flow += augmentFlow;
                    break;
                }
            }
            u = v;
        }

        flow += augmentFlow;
    }

    return flow;
}

int main() {
    int numNodes, numEdges;
    int source, sink;

    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter the source node: ";
    cin >> source;

    cout << "Enter the sink node: ";
    cin >> sink;

    vector<vector<Edge>> graph(numNodes);

    for (int i = 0; i < numEdges; i++) {
        int from, to, capacity;
        cout << "Enter edge " << i + 1 << ": ";
        cin >> from >> to >> capacity;

        Edge edge1 = {from, to, capacity, 0};
        Edge edge2 = {to, from, 0, 0};

        graph[from].push_back(edge1);
        graph[to].push_back(edge2);
    }

    int maxFlow = getMaxFlow(graph, source, sink);

    cout << "Maximum flow: " << maxFlow << endl;

    return 0;
}
