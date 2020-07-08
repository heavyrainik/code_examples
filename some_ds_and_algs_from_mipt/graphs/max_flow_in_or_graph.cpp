#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using std::vector;

struct Edge {
  Edge() {}
  Edge(int new_to, int new_capacity)
      : to(new_to), residual_capacity(new_capacity), current_flow(0) {}

  int to;
  int residual_capacity;
  int current_flow;
};

class TransportNet {
 public:
  TransportNet(int vertice_count) {
    stock_ = vertice_count - 1;
    graph_.resize(vertice_count);
  }

  void GraphInitialization(int edges_count) {
    graph_ = vector<vector<int>>(graph_.size(), vector<int>(graph_.size(), 0));
    current_edges_flow_ =
        vector<vector<int>>(graph_.size(), vector<int>(graph_.size(), 0));

    for (size_t i = 0; i < edges_count; ++i) {
      int from = 0;
      int to = 0;
      int residual_capacity = 0;

      std::cin >> from >> to >> residual_capacity;

      graph_[from - 1][to - 1] = residual_capacity;
    }
  }

  int FindMaxFlow() {
    int max_flow = 0;

    while (IsStockAccessable()) {
      first_undeleted_vertex_ = vector<int>(graph_.size(), 0);
      int flow = FindABlockingFlow(start_, INT_MAX);
      while (flow != 0) {
        max_flow += flow;
        flow = FindABlockingFlow(start_, INT_MAX);
      }
    }

    return max_flow;
  }

 private:
  int FindABlockingFlow(int from, int min_residual_capacity) {
    if (from == stock_ || min_residual_capacity == 0) {
      return min_residual_capacity;
    }

    for (int to = first_undeleted_vertex_[from]; to < graph_.size(); ++to) {
      if (argumeting_path_[to] == argumeting_path_[from] + 1) {
        int delta = FindABlockingFlow(
            to, std::min(min_residual_capacity,
                         graph_[from][to] - current_edges_flow_[from][to]));

        if (delta != 0) {
          current_edges_flow_[from][to] += delta;
          current_edges_flow_[to][from] -= delta;
          return delta;
        }
      }
      first_undeleted_vertex_[from]++;
    }
    return 0;
  }

  bool IsStockAccessable() {
    argumeting_path_ = vector<int>(graph_.size(), INT_MAX);
    std::queue<int> next_vertice;

    argumeting_path_[start_] = 0;
    next_vertice.push(start_);

    while (!next_vertice.empty()) {
      int current_vertex = next_vertice.front();

      next_vertice.pop();

      for (int next_vertex = 0; next_vertex < graph_[current_vertex].size();
           ++next_vertex) {
        if (current_edges_flow_[current_vertex][next_vertex] <
                graph_[current_vertex][next_vertex] &&
            argumeting_path_[next_vertex] == INT_MAX) {
          argumeting_path_[next_vertex] = argumeting_path_[current_vertex] + 1;
          next_vertice.push(next_vertex);
        }
      }
    }

    return argumeting_path_[stock_] != INT_MAX;
  }

  int stock_;
  int start_ = 0;
  vector<int> first_undeleted_vertex_;
  vector<int> argumeting_path_;
  vector<vector<int>> graph_;
  vector<vector<int>> current_edges_flow_;
};

int main() {
  size_t vertice_count = 0;
  size_t edges_count = 0;

  std::cin >> vertice_count >> edges_count;

  TransportNet graph(vertice_count);
  graph.GraphInitialization(edges_count);

  std::cout << graph.FindMaxFlow();

  return 0;
}
