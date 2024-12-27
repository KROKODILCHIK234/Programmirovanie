from collections import defaultdict
import heapq
from typing import Dict, List, Set, Tuple, Optional
import math

class Graph:
    def __init__(self, directed: bool = False, weighted: bool = False):
        self.directed = directed
        self.weighted = weighted
        self.adj_list = defaultdict(list)
        self.edge_weights = {}
        self.vertices = set()
    
    def add_edge(self, u: int, v: int, weight: float = 1.0) -> None:
        self.adj_list[u].append(v)
        self.vertices.add(u)
        self.vertices.add(v)
        
        if self.weighted:
            self.edge_weights[(u, v)] = weight
            
        if not self.directed and u != v:
            self.adj_list[v].append(u)
            if self.weighted:
                self.edge_weights[(v, u)] = weight
    
    def num_vertices(self) -> int:
        return len(self.vertices)
    
    def get_neighbors(self, u: int) -> List[int]:
        return self.adj_list.get(u, [])
    
    def get_weight(self, u: int, v: int) -> float:
        if not self.weighted:
            return 1.0
        return self.edge_weights.get((u, v), float('inf'))
    
    def get_vertices(self) -> Set[int]:
        return self.vertices
    
    def is_isomorphic_to(self, other: 'Graph') -> bool:
        if len(self.vertices) != len(other.vertices):
            return False
        
        degrees1 = sorted([len(self.adj_list[v]) for v in self.vertices])
        degrees2 = sorted([len(other.adj_list[v]) for v in other.vertices])
        
        return degrees1 == degrees2
    
    def dijkstra(self, start: int) -> Dict[int, Tuple[float, Optional[int]]]:
        """
        Реализация алгоритма Дейкстры для поиска кратчайших путей
        
        Args:
            start: Начальная вершина
            
        Returns:
            Dictionary, где ключ - вершина, значение - кортеж (расстояние, предыдущая вершина)
        """
        result = {v: (float('inf'), None) for v in self.vertices}
        result[start] = (0.0, start)
        
        # priority queue: (distance, vertex)
        pq = [(0.0, start)]
        visited = set()
        
        while pq and len(visited) < len(self.vertices):
            dist_u, u = heapq.heappop(pq)
            
            if u in visited:
                continue
                
            visited.add(u)
            
            for v in self.get_neighbors(u):
                if v in visited:
                    continue
                    
                weight = self.get_weight(u, v)
                new_dist = dist_u + weight
                
                if new_dist < result[v][0]:
                    result[v] = (new_dist, u)
                    heapq.heappush(pq, (new_dist, v))
        
        return result

    def get_shortest_path(self, start: int, end: int) -> Tuple[List[int], float]:
        """
        Находит кратчайший путь между двумя вершинами
        
        Args:
            start: Начальная вершина
            end: Конечная вершина
            
        Returns:
            Кортеж (путь, длина_пути)
        """
        distances = self.dijkstra(start)
        if distances[end][0] == float('inf'):
            return [], float('inf')
            
        path = []
        current = end
        
        while current != start:
            path.append(current)
            current = distances[current][1]
            
        path.append(start)
        path.reverse()
        
        return path, distances[end][0]

# Пример использования
if __name__ == "__main__":
    # Создаем взвешенный направленный граф
    g = Graph(directed=True, weighted=True)
    
    # Добавляем рёбра
    g.add_edge(0, 1, 4)
    g.add_edge(0, 2, 2)
    g.add_edge(1, 2, 1)
    g.add_edge(1, 3, 5)
    g.add_edge(2, 3, 8)
    g.add_edge(2, 4, 10)
    g.add_edge(3, 4, 2)
    
    # Находим кратчайшие пути из вершины 0
    distances = g.dijkstra(0)
    print("Кратчайшие расстояния от вершины 0:")
    for vertex, (dist, prev) in distances.items():
        print(f"До вершины {vertex}: расстояние = {dist}, предыдущая вершина = {prev}")
    
    # Находим кратчайший путь между двумя вершинами
    path, distance = g.get_shortest_path(0, 4)
    print(f"\nКратчайший путь от 0 до 4:")
    print(f"Путь: {path}")
    print(f"Расстояние: {distance}")
