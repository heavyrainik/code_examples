#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

struct Vertex {
  Vertex() : paths(0), depth(0) {}

  int depth;
  int paths;
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

int FindMinPath(const ListGraph& graph, int from, int to) {
  int vertices_count = graph.VertexCount();
  vector<Vertex> vertices_states(vertices_count);
  queue<int> vertices;

  vertices.push(from);
  vertices_states[from].paths = 1;

  vector<int> next_vertices;

  while (!vertices.empty()) {
    int current_vertex = vertices.front();
    vertices.pop();
    graph.GetNextVertices(current_vertex, next_vertices);

    for (int vertex : next_vertices) {
      if (vertices_states[vertex].paths == 0) {
        vertices_states[vertex].depth =
            vertices_states[current_vertex].depth + 1;
        vertices_states[vertex].paths = vertices_states[current_vertex].paths;

        vertices.push(vertex);
      } else {
        if (vertices_states[vertex].depth ==
            vertices_states[current_vertex].depth + 1) {
          vertices_states[vertex].paths +=
              vertices_states[current_vertex].paths;
        }
      }
    }
  }

  return vertices_states[to].paths;
}

int main() {
  int vertex_count = 0;
  int edges_count = 0;
  int from = -1;
  int to = -1;

  std::cin >> vertex_count >> edges_count;

  ListGraph graph(vertex_count);

  for (int i = 0; i < edges_count; ++i) {
    std::cin >> from >> to;

    graph.AddEdge(from, to);
  }

  std::cin >> from >> to;

  std::cout << FindMinPath(graph, from, to);

  return 0;
}
