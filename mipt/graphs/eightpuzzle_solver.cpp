#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using std::shared_ptr;
using std::vector;

class Node : public std::enable_shared_from_this<Node> {
 public:
  shared_ptr<Node> parent;

  Node(vector<int>& current_field_state, int weight, char direction,
       const int field_size) {
    field_size_ = field_size;
    current_field_state_ = current_field_state;
    CalculateEvristic();
    distance_from_root_ = weight;
    direction_ = direction;
    parent = nullptr;
  }

  void CalculateEvristic() {
    int evristic_distance = 0;

    for (int i = 0; i < field_size_ * field_size_; ++i) {
      if (current_field_state_[i] != 0) {
        evristic_distance += abs((current_field_state_[i] - 1) / field_size_ -
                                 (i) / field_size_) +
                             abs((current_field_state_[i] - 1) % field_size_ -
                                 (i) % field_size_);
      }
    }

    evristic_distance_ = evristic_distance;
  }

  const vector<int>& GetState() const { return current_field_state_; }

  int GetState(int index) const { return current_field_state_[index]; }

  void AddChild(vector<int>& arr, char direction_, const size_t field_size) {
    shared_ptr<Node> v = std::make_shared<Node>(arr, distance_from_root_ + 1,
                                                direction_, field_size);

    v->parent = shared_from_this();
    next_vertice_.push_back(std::move(v));
  }

  size_t GetChildrenCount() const { return next_vertice_.size(); }

  int GetDirection() { return direction_; }

  shared_ptr<Node> GetChild(int index) { return next_vertice_[index]; }

  int GetPosition(int index) const {
    int pos = 0;

    for (size_t i = 0; i < field_size_ * field_size_; ++i) {
      if (current_field_state_[i] == index) {
        pos = i;
      }
    }

    return pos;
  }

  int GetEvristicDistance() const { return evristic_distance_; }

  int GetDistanceFromRoot() const { return distance_from_root_; }

 private:
  int field_size_;
  vector<int> current_field_state_;
  vector<shared_ptr<Node>> next_vertice_;
  int evristic_distance_;
  int distance_from_root_;
  char direction_;
};

struct PriorityQueueComparator {
  bool operator()(shared_ptr<Node> v1, shared_ptr<Node> v2) {
    return (v1->GetEvristicDistance() + v1->GetDistanceFromRoot() >
            v2->GetEvristicDistance() + v2->GetDistanceFromRoot());
  }
};

class EightPuzzleSolver {
 public:
  EightPuzzleSolver(const vector<int>& current_field_state_,
                    const int field_size) {
    field_size_ = field_size;
    start_state_ = current_field_state_;
    root_ = std::make_shared<Node>(start_state_, 0, '0', field_size);
  }

  bool CheckIfIsHasASolution() {
    size_t inversion_count = 0;

    for (size_t i = 1; i < field_size_ * field_size_; ++i) {
      int position = root_->GetPosition(i);

      position++;
      while (position <= field_size_ * field_size_ - 1) {
        if (root_->GetState(position) < i && root_->GetState(position) != 0) {
          inversion_count++;
        }
        position++;
      }
    }

    if (inversion_count % 2) {
      return false;
    }

    return true;
  }

  bool CheckIfCorner(vector<char>& directions, int node_position) {
    if (node_position == 0) {
      directions.push_back('R');
      directions.push_back('D');
      return true;
    } else if (node_position == field_size_ - 1) {
      directions.push_back('L');
      directions.push_back('D');
      return true;
    } else if (node_position == field_size_ * field_size_ - 1) {
      directions.push_back('U');
      directions.push_back('L');
      return true;
    } else if (node_position == field_size_ * field_size_ - field_size_) {
      directions.push_back('R');
      directions.push_back('U');
      return true;
    }

    return false;
  }

  void CheckOtherPositions(vector<char>& directions, int node_position) {
    if (node_position % field_size_ == 0) {
      directions.push_back('U');
      directions.push_back('R');
      directions.push_back('D');
    } else if (node_position % field_size_ == field_size_ - 1) {
      directions.push_back('U');
      directions.push_back('D');
      directions.push_back('L');
    } else if (node_position / field_size_ == 0) {
      directions.push_back('D');
      directions.push_back('L');
      directions.push_back('R');
    } else if (node_position / field_size_ == field_size_ - 1) {
      directions.push_back('U');
      directions.push_back('R');
      directions.push_back('L');
    } else {
      directions.push_back('U');
      directions.push_back('D');
      directions.push_back('L');
      directions.push_back('R');
    }
  }

  void GetFollowingState(shared_ptr<Node>& current_node,
                         vector<char>& directions) {
    auto current_state = current_node->GetState();

    for (size_t i = 0; i < directions.size(); i++) {
      auto next_state = current_state;
      int position = current_node->GetPosition(0);

      if (directions[i] == 'R') {
        std::swap(next_state[position], next_state[position + 1]);
      } else if (directions[i] == 'L') {
        std::swap(next_state[position], next_state[position - 1]);
      } else if (directions[i] == 'U') {
        std::swap(next_state[position], next_state[position - field_size_]);
      } else if (directions[i] == 'D') {
        std::swap(next_state[position], next_state[position + field_size_]);
      }

      if (watched_nodes_.find(next_state) == watched_nodes_.end()) {
        current_node->AddChild(next_state, directions[i], field_size_);
      }
    }
  }

  std::pair<int, std::string> GetMovesCountAndPath(
      shared_ptr<Node>& current_node) {
    std::string path_from_node_to_root;
    int moves_count = 0;

    while (current_node != root_) {
      path_from_node_to_root.push_back(current_node->GetDirection());
      current_node = current_node->parent;
      ++moves_count;
    }

    std::string path_from_root_to_node;

    for (int i = path_from_node_to_root.size() - 1; i >= 0; --i) {
      path_from_root_to_node.push_back(path_from_node_to_root[i]);
    }

    return std::pair<int, std::string>(moves_count, path_from_root_to_node);
  }

  std::pair<int, std::string> Solve() {
    if (!CheckIfIsHasASolution()) {
      std::pair<int, std::string> pair(-1, "no solution");
      return pair;
    }

    std::priority_queue<shared_ptr<Node>, std::deque<shared_ptr<Node>>,
                        PriorityQueueComparator>
        next_nodes;
    shared_ptr<Node> current_node = root_;
    next_nodes.push(current_node);

    while (true) {
      current_node = next_nodes.top();

      if (current_node->GetEvristicDistance() == 0) {
        break;
      }

      vector<char> directions;
      int node_position = current_node->GetPosition(0);

      if (!CheckIfCorner(directions, node_position)) {
        CheckOtherPositions(directions, node_position);
      }

      GetFollowingState(current_node, directions);

      watched_nodes_.insert(next_nodes.top()->GetState());
      next_nodes.pop();

      for (size_t i = 0; i < current_node->GetChildrenCount(); ++i) {
        next_nodes.push(current_node->GetChild(i));
      }
    }

    return GetMovesCountAndPath(current_node);
  }

 private:
  int field_size_;
  vector<int> start_state_;
  std::set<vector<int>> watched_nodes_;
  shared_ptr<Node> root_;
};

int main() {
  vector<int> current_field_state_;
  const int field_size = 3;

  for (size_t i = 0; i < field_size * field_size; ++i) {
    int value = 0;

    std::cin >> value;
    current_field_state_.push_back(value);
  }

  EightPuzzleSolver solver(current_field_state_, field_size);

  std::pair<int, std::string> answer = solver.Solve();

  if (answer.first == -1) {
    std::cout << answer.first;
  } else {
    std::cout << answer.first << "\n" << answer.second;
  }

  return 0;
}
//что значит нет