#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using std::vector;

struct Edge {
  Edge(int new_to, int new_capacity)
      : to(new_to), residual_capacity(new_capacity), current_flow(0) {}

  int to = -1;
  int residual_capacity = 0;
  int current_flow = 0;
};

class TransportNet {
 public:
  TransportNet(int vertice_count) {
    sink_ = vertice_count - 1;
    graph_.resize(vertice_count);
    graph_ = vector<vector<int>>(vertice_count, vector<int>(vertice_count, 0));
  }

  void GraphInitialization(int workers_count, int tea_bags_count) {
    workers_count_ = workers_count;
    vector<int> tea_sort_bags_count(tea_bags_count, 0);

    for (int i = 0; i < tea_bags_count; ++i) {
      std::cin >> tea_sort_bags_count[i];
      tea_bags_count_ += tea_sort_bags_count[i];
    }

    for (int from = 1; from <= workers_count; ++from) {
      int favourite_flavor_count = 0;

      std::cin >> favourite_flavor_count;

      for (int j = 0; j < favourite_flavor_count; ++j) {
        int favourite_flavor = -1;

        std::cin >> favourite_flavor;

        graph_[from][workers_count + favourite_flavor] =
            std::numeric_limits<int>::max();
      }
    }

    for (int from = workers_count + 1; from < sink_; ++from) {
      graph_[from][sink_] = tea_sort_bags_count[from - workers_count - 1];
    }
  }

  int FindMaxAmountOfDays() {
    int left_border = 0;
        int right_border = tea_bags_count_ + 1;
        int mid_elem = 1;
        
        while (left_border != right_border) {
            mid_elem = (left_border + right_border) / 2 + 1;
            
            for (int from = 1; from < workers_count_ + 1; ++from) {
                graph_[source_][from] = mid_elem;
            }
            
            int max_flow = FindMaxFlow();
//            Show();
            
            if (max_flow == workers_count_ * mid_elem) {
                left_border = mid_elem;
            } else {
                right_border = mid_elem - 1;
            }
        }
        return left_border;
  }

 private:
  int FindMaxFlow() {
    edges_flow_ = vector<vector<int>>(sink_ + 1, vector<int>(sink_ + 1, 0));
    int max_flow = 0;

    while (IsStockAccessable()) {
      first_suitable_vertex_ = vector<int>(graph_.size(), 0);
      int flow = FindABlockingFlow(source_, std::numeric_limits<int>::max());
      while (flow != 0) {
        max_flow += flow;
        flow = FindABlockingFlow(source_, std::numeric_limits<int>::max());
      }
    }

    return max_flow;
  }

  void Show() {
    for (int i = 0; i <= sink_; ++i) {
      for (int j = 0; j < sink_ + 1; ++j) {
        std::cout << graph_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  int FindABlockingFlow(int from, int min_residual_capacity) {
    if (from == sink_ || min_residual_capacity == 0) {
      return min_residual_capacity;
    }

    for (int to = first_suitable_vertex_[from]; to < graph_.size(); ++to) {
      if (argumeting_path_[to] == argumeting_path_[from] + 1) {
        int delta = FindABlockingFlow(
            to, std::min(min_residual_capacity,
                         graph_[from][to] - edges_flow_[from][to]));

        if (delta != 0) {
          edges_flow_[from][to] += delta;
          edges_flow_[to][from] -= delta;
          return delta;
        }
      }
      first_suitable_vertex_[from]++;
    }
    return 0;
  }

  bool IsStockAccessable() {
    argumeting_path_ =
        vector<int>(graph_.size(), std::numeric_limits<int>::max());
    std::queue<int> next_vertice;

    argumeting_path_[source_] = 0;
    next_vertice.push(source_);

    while (!next_vertice.empty()) {
      int current_vertex = next_vertice.front();

      next_vertice.pop();

      for (int next_vertex = 0; next_vertex < graph_[current_vertex].size();
           ++next_vertex) {
        if (edges_flow_[current_vertex][next_vertex] <
                graph_[current_vertex][next_vertex] &&
            argumeting_path_[next_vertex] == std::numeric_limits<int>::max()) {
          argumeting_path_[next_vertex] = argumeting_path_[current_vertex] + 1;
          next_vertice.push(next_vertex);
        }
      }
    }

    return argumeting_path_[sink_] != std::numeric_limits<int>::max();
  }

  int sink_;
  int source_ = 0;
  int workers_count_;
  int tea_bags_count_ = 0;
  vector<int> first_suitable_vertex_;
  vector<int> argumeting_path_;
  vector<vector<int>> graph_;
  vector<vector<int>> edges_flow_;
};

int main() {
  size_t workers_count = 0;
  size_t tea_sorts_amount = 0;

  std::cin >> workers_count >> tea_sorts_amount;

  TransportNet graph(workers_count + 1 + tea_sorts_amount + 1);
  graph.GraphInitialization(workers_count, tea_sorts_amount);

  std::cout << graph.FindMaxAmountOfDays();

  return 0;
}
