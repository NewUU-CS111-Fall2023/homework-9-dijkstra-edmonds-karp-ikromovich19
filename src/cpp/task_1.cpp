#include <iostream>
#include <vector>
#include <queue>
#include <limits>


struct Vertex {
    int id;    
    int d;     
    int π;     
};


struct Edge {
    int u;   
    int v;   
    int weight;  
};


void initializeSingleSource(std::vector<Vertex>& graph, int source) {
    for (int i = 0; i < graph.size(); i++) {
        graph[i].d = std::numeric_limits<int>::max();
        graph[i].π = -1;
    }
    graph[source].d = 0;
}


void relax(std::vector<Vertex>& graph, Edge& e) {
    int u = e.u;
    int v = e.v;
    int weight = e.weight;
    if (graph[v].d > graph[u].d + weight) {
        graph[v].d = graph[u].d + weight;
        graph[v].π = u;
    }
}


void dijkstra(std::vector<std::vector<Edge>>& G, std::vector<Vertex>& graph, int source) {
    initializeSingleSource(graph, source);
    std::vector<bool> visited(graph.size(), false);

  
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> Q;
    Q.push(std::make_pair(graph[source].d, source));

    while (!Q.empty()) {
        int u = Q.top().second;
        Q.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (auto& edge : G[u]) {
            relax(graph, edge);
            if (!visited[edge.v]) {
                Q.push(std::make_pair(graph[edge.v].d, edge.v));
            }
        }
    }   
}


int main() {
    int numVertices, numEdges, source;
    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;
    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    std::vector<Vertex> graph(numVertices);
    std::vector<std::vector<Edge>> G(numVertices);

    std::cout << "Enter the edges (u, v, weight):" << std::endl;
    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        std::cin >> u >> v >> weight;
        Edge e = {u, v, weight};
        G[u].push_back(e);
    }

    std::cout << "Enter the source vertex: ";
    std::cin >> source;

    dijkstra(G, graph, source);

    std::cout << "Shortest distances from source to each vertex:" << std::endl;
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertex " << i << ": " << graph[i].d << std::endl;
    }

    return 0;
}
