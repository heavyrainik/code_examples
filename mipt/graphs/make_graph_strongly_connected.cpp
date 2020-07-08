#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

class MatrixGraph {
 public:
  MatrixGraph() = delete;
  explicit MatrixGraph(size_t vertices_count);

  void AddEdge(int from, int to);

  void GetNextVertices(int vertex, vector<int>& next_vertices) const;
  void GetPrevVertices(int vertex, vector<int>& prev_vertices) const;

  int GetVerticesCount() const;

 private:
  vector<vector<int>> graph_;
  size_t vertices_count_;
};

MatrixGraph::MatrixGraph(size_t vertices_count)
    : vertices_count_(vertices_count),
      graph_(vertices_count, vector<int>(vertices_count, 0)) {}

void MatrixGraph::AddEdge(int from, int to) { graph_[from][to] = 1; }

void MatrixGraph::GetNextVertices(int vertex,
                                  vector<int>& next_vertices) const {
  for (int current_vertex = 0; current_vertex < GetVerticesCount();
       ++current_vertex) {
    if (graph_[vertex][current_vertex] != 0) {
      next_vertices.push_back(current_vertex);
    }
  }
}

void MatrixGraph::GetPrevVertices(int vertex,
                                  vector<int>& prev_vertices) const {
  for (int current_vertex = 0; current_vertex < GetVerticesCount();
       ++current_vertex) {
    if (graph_[current_vertex][vertex] != 0) {
      prev_vertices.push_back(current_vertex);
    }
  }
}

int MatrixGraph::GetVerticesCount() const { return vertices_count_; }

void DFSOnInvertedGraph(int vertex, vector<int>& vertice_states,
                        vector<int>& times_out, MatrixGraph& graph) {
  vector<int> previous_vertice;

  previous_vertice.clear();
  graph.GetPrevVertices(vertex, previous_vertice);
  vertice_states[vertex] = 1;

  for (int next_vertex : previous_vertice) {
    if (vertice_states[next_vertex] == 0) {
      DFSOnInvertedGraph(next_vertex, vertice_states, times_out, graph);
    }
  }

  times_out.push_back(vertex);
}

void DFS(int vertex, vector<int>& vertice_states,
         vector<int>& strongly_connected_components, int scc_number,
         MatrixGraph& graph) {
  vector<int> next_vertice;

  next_vertice.clear();
  graph.GetNextVertices(vertex, next_vertice);
  vertice_states[vertex] = 1;

  for (int next_vertex : next_vertice) {
    if (vertice_states[next_vertex] == 0) {
      DFS(next_vertex, vertice_states, strongly_connected_components,
          scc_number, graph);
    }
  }

  strongly_connected_components[vertex] = scc_number;
}

int KosarayuAlgorithm(vector<int>& strongly_connected_components,
                      MatrixGraph& graph) {
  int vertice_count = graph.GetVerticesCount();
  int scc_amount = 0;
  vector<int> times_out;
  vector<int> vertice_states(vertice_count, 0);

  for (int vertex = 0; vertex < vertice_count; ++vertex) {
    if (vertice_states[vertex] == 0) {
      DFSOnInvertedGraph(vertex, vertice_states, times_out, graph);
    }
  }

  for (int vertex = 0; vertex < vertice_states.size(); ++vertex) {
    vertice_states[vertex] = 0;
  }

  for (int vertex = times_out.size() - 1; vertex > -1; --vertex) {
    if (vertice_states[times_out[vertex]] == 0) {
      DFS(times_out[vertex], vertice_states, strongly_connected_components,
          scc_amount, graph);
      ++scc_amount;
    }
  }

  return scc_amount;
}

int MakeGraphStronglyConnected(MatrixGraph& graph) {
  int stock_vertice_count = 0;
  int outstock_vertice_count = 0;
  int vertice_count = graph.GetVerticesCount();
  vector<int> strongly_connected_components(vertice_count, -1);
  vector<int> vertice_states(vertice_count, 0);
  vector<int> next_vertice;
  queue<int> vertice;

  int scc_amount = KosarayuAlgorithm(strongly_connected_components, graph);

  vector<int> stock_vertice(scc_amount, 1);
  vector<int> outstock_vertice(scc_amount, 1);

  if (scc_amount == 1) {
    return 0;
  }

  for (int vertex = 0; vertex < vertice_count; ++vertex) {
    if (vertice_states[vertex] == 0) {
      vertice.push(vertex);
    }

    while (!vertice.empty()) {
      int current_vertex = vertice.front();

      vertice_states[current_vertex] = 1;
      vertice.pop();
      next_vertice.clear();
      graph.GetNextVertices(current_vertex, next_vertice);

      for (int next_vertex : next_vertice) {
        if (strongly_connected_components[current_vertex] !=
            strongly_connected_components[next_vertex]) {
          stock_vertice[strongly_connected_components[current_vertex]] = 0;
          outstock_vertice[strongly_connected_components[next_vertex]] = 0;
        }
        if (vertice_states[next_vertex] == 0) {
          vertice.push(next_vertex);
        }
      }
    }
  }

  for (int scc = 0; scc < scc_amount; ++scc) {
    if (stock_vertice[scc] != 0) {
      stock_vertice_count++;
    }
    if (outstock_vertice[scc] != 0) {
      outstock_vertice_count++;
    }
  }

  if (stock_vertice_count > outstock_vertice_count) {
    return stock_vertice_count;
  }
  return outstock_vertice_count;
}

int main() {
  int vertice_count = 0;
  int edges_count = 0;

  std::cin >> vertice_count >> edges_count;

  MatrixGraph graph(vertice_count);

  for (int i = 0; i < edges_count; ++i) {
    int from = -1;
    int to = -1;

    std::cin >> from >> to;

    if (from != to) {
      graph.AddEdge(from - 1, to - 1);
    }
  }

  std::cout << MakeGraphStronglyConnected(graph);

  return 0;
}
