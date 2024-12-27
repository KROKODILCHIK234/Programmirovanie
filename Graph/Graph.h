#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <limits>
#include <unordered_map>

class Graph {
public:
    Graph(bool directed = false, bool weighted = false);
    void addEdge(int u, int v, double weight = 1.0);
    int numVertices() const;
    const std::vector<int>& getNeighbors(int u) const;
    double getWeight(int u, int v) const;
    const std::set<int>& getVertices() const;
    bool isIsomorphicTo(const Graph& other) const;
    bool isDirected() const { return directed; }
    std::map<int, std::pair<double, int>> dijkstra(int start) const;

private:
    bool directed;
    bool weighted;
    std::unordered_map<int, std::vector<int>> adjList;
    std::unordered_map<int64_t, double> edgeWeights;
    std::set<int> vertices;
    
    inline int64_t getEdgeKey(int u, int v) const {
        return (static_cast<int64_t>(u) << 32) | static_cast<int64_t>(v);
    }
};

#endif
