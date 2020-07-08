#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

class ListGraph {
 public:
  ListGraph(size_t vertices_count);

  void AddEdge(int from, int to);

  void GetNextVertices(int vertex, vector<int>& next_vertices) const;
  void GetPrevVertices(int vertex, vector<int>& prev_vertices) const;

  int GetVerticesCount() const;

 private:
  vector<vector<int>> graph_;
  size_t vertices_count_;
};

void ListGraph::GetNextVertices(int vertex, vector<int>& next_vertices) const {
  next_vertices = graph_[vertex];
}

void ListGraph::GetPrevVertices(int vertex, vector<int>& prev_vertices) const {
  for (int vertex = 0; vertex < GetVerticesCount(); ++vertex) {
    for (int current_vertex : graph_[vertex]) {
      if (current_vertex == vertex) {
        prev_vertices.push_back(current_vertex);
      }
    }
  }
}

int ListGraph::GetVerticesCount() const { return vertices_count_; }

void ListGraph::AddEdge(int from, int to) { graph_[from].push_back(to); }

ListGraph::ListGraph(size_t vertices_count) {
  vertices_count_ = vertices_count;
  graph_.resize(vertices_count_);
  for (int i = 0; i < vertices_count_; ++i) {
    graph_[i].resize(0);
  }
}

bool IsDicotyledonous(ListGraph graph) {
  vector<int> part(graph.GetVerticesCount(), -1);
  vector<int> next_vertice;
  queue<int> vertice;

  vertice.push(0);
  part[0] = 0;

  while (!vertice.empty()) {
    int current_vertex = vertice.front();
    vertice.pop();

    graph.GetNextVertices(current_vertex, next_vertice);

    for (int vertex : next_vertice) {
      if (part[vertex] == -1) {
        vertice.push(vertex);

        part[vertex] = (part[current_vertex] + 1) % 2;
      } else {
        if (part[vertex] == part[current_vertex]) {
          return false;
        }
      }
    }

    next_vertice.clear();
  }

  return true;
}

int main() {
  int vertice_count = 0;
  int edges_count = 0;

  std::cin >> vertice_count >> edges_count;

  ListGraph graph(vertice_count);

  for (int i = 0; i < edges_count; ++i) {
    int from = -1;
    int to = -1;

    std::cin >> from >> to;

    graph.AddEdge(from, to);
    graph.AddEdge(to, from);
  }

  if (IsDicotyledonous(graph)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }

  return 0;
}
