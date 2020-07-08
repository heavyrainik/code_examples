#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

struct Vertex {
  Vertex() : length(0), is_visited(false) {}

  int previous_vertex;
  int length;
  bool is_visited;
};

class ListGraph {
 public:
  ListGraph(int vertex_count) {
    vertex_count_ = vertex_count;
    graph_.resize(vertex_count);

    for (int i = 0; i < vertex_count; ++i) {
      graph_[i].resize(0);
    }
  }
  ~ListGraph() {}

  void AddEdge(int from, int to) {
    graph_[to].push_back(from);
    graph_[from].push_back(to);
  }
  int VertexCount() const { return vertex_count_; };

  void GetNextVertices(int vertex, vector<int>& vertices) const {
    vertices.clear();
    for (int vertice : graph_[vertex]) {
      vertices.push_back(vertice);
    }
  }

 private:
  vector<vector<int>> graph_;
  int vertex_count_;
};

int FindACicle(const ListGraph& graph, int vertex) {
  int vertex_count = graph.VertexCount();
  vector<Vertex> vertices_states(vertex_count);
  queue<int> vertices;

  vertices.push(vertex);
  vertices_states[vertex].is_visited = true;

  vector<int> next_vertices;

  while (!vertices.empty()) {
    int current_vertex = vertices.front();
    vertices.pop();

    graph.GetNextVertices(current_vertex, next_vertices);

    for (int vertex : next_vertices) {
      if (!vertices_states[vertex].is_visited) {
        vertices_states[vertex].is_visited = true;
        vertices_states[vertex].previous_vertex = current_vertex;
        vertices_states[vertex].length =
            vertices_states[current_vertex].length + 1;

        vertices.push(vertex);
      } else {
        if (vertex != vertices_states[current_vertex].previous_vertex) {
          return vertices_states[current_vertex].length +
                 vertices_states[vertex].length + 1;
        }
      }
    }
  }
  return vertex_count + 1;
}

int FindMinCycle(ListGraph& graph) {
  int vertex_count = graph.VertexCount();
  int min_cycle_lenght = vertex_count + 1;

  for (int i = 0; i < vertex_count; ++i) {
    int current_cycle_lenght = FindACicle(graph, i);

    if (current_cycle_lenght < min_cycle_lenght) {
      min_cycle_lenght = current_cycle_lenght;
    }
  }

  if (min_cycle_lenght != vertex_count + 1) {
    return min_cycle_lenght;
  }

  return -1;
}

int main() {
  int vertex_count = 0;
  int edges_count = 0;

  std::cin >> vertex_count >> edges_count;

  ListGraph graph(vertex_count);

  for (int i = 0; i < edges_count; ++i) {
    int from = -1;
    int to = -1;

    std::cin >> from >> to;
    graph.AddEdge(from, to);
  }

  std::cout << FindMinCycle(graph);

  return 0;
}
