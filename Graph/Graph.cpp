#include "Graph.h"
#include <algorithm>
#include <queue>
#include <limits>
#include <unordered_set>

Graph::Graph(bool directed, bool weighted)
    : directed(directed), weighted(weighted) {}

void Graph::addEdge(int u, int v, double weight) {
    adjList[u].push_back(v);
    vertices.insert(u);
    vertices.insert(v);
    
    if (weighted) {
        edgeWeights[getEdgeKey(u, v)] = weight;
    }
    
    if (!directed && u != v) {
        adjList[v].push_back(u);
        if (weighted) {
            edgeWeights[getEdgeKey(v, u)] = weight;
        }
    }
}

int Graph::numVertices() const {
    return vertices.size();
}

const std::vector<int>& Graph::getNeighbors(int u) const {
    static const std::vector<int> empty;
    auto it = adjList.find(u);
    return it != adjList.end() ? it->second : empty;
}

double Graph::getWeight(int u, int v) const {
    if (!weighted) return 1.0;
    
    auto it = edgeWeights.find(getEdgeKey(u, v));
    return it != edgeWeights.end() ? it->second : std::numeric_limits<double>::infinity();
}

const std::set<int>& Graph::getVertices() const {
    return vertices;
}

bool Graph::isIsomorphicTo(const Graph& other) const {
    if (vertices.size() != other.vertices.size()) return false;
    
    std::vector<size_t> degrees1, degrees2;
    degrees1.reserve(vertices.size());
    degrees2.reserve(other.vertices.size());
    
    for (int v : vertices) degrees1.push_back(adjList.at(v).size());
    for (int v : other.vertices) degrees2.push_back(other.adjList.at(v).size());
    
    std::sort(degrees1.begin(), degrees1.end());
    std::sort(degrees2.begin(), degrees2.end());
    
    return degrees1 == degrees2;
}

std::map<int, std::pair<double, int>> Graph::dijkstra(int start) const {
    std::map<int, std::pair<double, int>> result;
    std::priority_queue<std::pair<double, int>, 
                       std::vector<std::pair<double, int>>, 
                       std::greater<>> pq;
    std::unordered_set<int> visited;
    
    for (int v : vertices) {
        result[v] = {std::numeric_limits<double>::infinity(), -1};
    }
    
    result[start] = {0.0, start};
    pq.push({0.0, start});
    
    while (!pq.empty() && visited.size() < vertices.size()) {
        auto [dist_u, u] = pq.top();
        pq.pop();
        
        if (visited.count(u)) continue;
        visited.insert(u);
        
        for (int v : getNeighbors(u)) {
            if (visited.count(v)) continue;
            
            double weight = getWeight(u, v);
            double new_dist = dist_u + weight;
            
            if (new_dist < result[v].first) {
                result[v] = {new_dist, u};
                pq.push({new_dist, v});
            }
        }
    }
    
    return result;
}
