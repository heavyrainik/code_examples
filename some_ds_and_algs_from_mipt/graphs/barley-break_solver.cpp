#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <queue>
#include <set>


struct PuzzleSolution {
  PuzzleSolution(unsigned long long pos, std::string new_way, int distance, int poss_heuristic_distance) {
    null_position = pos;
    way_ = new_way;
    distance_ = distance;
    heuristic_distance_ = poss_heuristic_distance;
  }

  unsigned long long null_position = 0;
  std::string way_ = "";
  int distance_ = 0;
  int heuristic_distance_ = 0;
};


class PuzzleState {
public:
  PuzzleState(unsigned long long starting_position, std::string way, int heuristic_distance, int field_size) {
    field_size_ = field_size;
    way_ = way;
    distance_ = heuristic_distance;
    heuristic_distance_ = 0;

    CountHeuristics(starting_position);
  }

  std::string GetWay() {
    return way_;
  }

  int GetDistanation() const {
    return distance_;
  }

  int GetPossibleDistanation() const {
    return heuristic_distance_;
  }

  std::array<int, 16> GetCurrentState() const {
    return state_;
  }

  int GetFieldSize() const {
    return field_size_;
  }

  int FindNullPosition() {
    for (int i = 0; i < state_.size(); i++) {
      if (state_[i] == 0) {
        return i;
      }
    }
  }

  void CountHeuristics(unsigned long long starting_position) {
    for (int i = 0; i < field_size_*field_size_; ++i) {
      state_[field_size_*field_size_ - 1 - i] = starting_position & (field_size_*field_size_ - 1);
      starting_position = starting_position >> field_size_;
    }

    for (int i = 0; i < field_size_*field_size_; ++i) {
      if (state_[i] != 0) {
        heuristic_distance_ = heuristic_distance_ + abs((state_[i] - 1) / field_size_ - (i / field_size_)) + abs((state_[i] - 1) % field_size_ - (i % field_size_));
      }
    }

    for (int i = 0; i < field_size_; ++i) {
      for (int j = 0; j < field_size_; ++j) {
        if (state_[j + field_size_ * i] != 0 && (state_[j + field_size_ * i] - 1) / field_size_ - (j + field_size_ * i) / field_size_ == 0) {
          for (int k = j; k < field_size_; ++k) {
            if (state_[k + field_size_ * i] != 0 && (state_[k + field_size_ * i] < state_[j + field_size_ * i]) && (state_[k + field_size_ * i] - 1) / field_size_ - (k + field_size_ * i) / field_size_ == 0) {
              heuristic_distance_ = heuristic_distance_ + 2;
            }
          }
        }
      }
    }

    for (int i = 0; i < field_size_; ++i) {
      for (int j = 0; j < field_size_; ++j) {
        if (state_[j * field_size_ + i] != 0 && (state_[j * field_size_ + i] - 1) % field_size_ - (j * field_size_ + i) % field_size_ == 0) {
          for (int k = j; k < field_size_; ++k) {
            if (state_[k * field_size_ + i] != 0 && (state_[k * field_size_ + i] < state_[j * field_size_ + i]) && (state_[k * field_size_ + i] - 1) % field_size_ - (k * field_size_ + i) % field_size_ == 0) {
              heuristic_distance_ = heuristic_distance_ + 2;
            }
          }
        }
      }
    }
  }

  unsigned long long MyHash(std::array<int, 16> position_) {
    unsigned long long tmp = 0;

    for (int i = 0; i < position_.size(); ++i) {
      tmp = (tmp << field_size_) + position_[i];
    }

    return tmp;
  }

  PuzzleSolution GetInformation() {
    return PuzzleSolution(MyHash(state_), way_, distance_, heuristic_distance_);
  }

  unsigned long long NextState(PuzzleState prevPos, int null_position, std::string i) {
    if (i == "U") {
      std::swap(prevPos.state_[null_position], prevPos.state_[null_position - field_size_]);
    }
    if (i == "D") {
      std::swap(prevPos.state_[null_position], prevPos.state_[null_position + field_size_]);
    }
    if (i == "R") {
      std::swap(prevPos.state_[null_position], prevPos.state_[null_position + 1]);
    }
    if (i == "L") {
      std::swap(prevPos.state_[null_position], prevPos.state_[null_position - 1]);
    }
    return MyHash(prevPos.state_);
  }

private:
  int field_size_ = 4;
  std::array<int, 16> state_;
  int distance_;
  std::string way_;
  int heuristic_distance_;
};

const bool operator < (const PuzzleState &arg1, const PuzzleState &arg2) {
  if (arg1.GetPossibleDistanation() + 0.55 * arg1.GetDistanation() < arg2.GetPossibleDistanation() + 0.55 * arg2.GetDistanation()) {
    return false;
  }
  return true;
}

bool HasSolution(PuzzleState vert) {
  int field_size = vert.GetFieldSize();
  std::array<int, 16> starting_state = vert.GetCurrentState();
  int invertion_count = 0;

  for (int i = 0; i < field_size*field_size; ++i) {
    if (starting_state[i] == 0) {
      invertion_count = invertion_count + i / field_size + 1;
    }
    else {
      int l = 0;
      for (int j = i; j < field_size*field_size; ++j) {
        if (starting_state[i] > starting_state[j] && starting_state[j] != 0) {
          l++;
        }
      }
      invertion_count = invertion_count + l;
    }
  }
  if (invertion_count % 2 == 0) {
    return true;
  }
  return false;
}

void FindNextPuzzleStates(PuzzleState& current_puzzle_state, std::set<unsigned long long>& processed_states, std::priority_queue<PuzzleState>& next_states) {
  int null_position = current_puzzle_state.FindNullPosition();
  int field_size = current_puzzle_state.GetFieldSize();

  if (null_position > 3) {
    unsigned long long hash = current_puzzle_state.NextState(current_puzzle_state, null_position, "U");

    if (processed_states.find(hash) == processed_states.end()) {
      processed_states.insert(hash);
      next_states.push(PuzzleState(hash, current_puzzle_state.GetWay() + "D", current_puzzle_state.GetDistanation() + 1, field_size));
    }
  }
  if (null_position < 12) {
    unsigned long long hash = current_puzzle_state.NextState(current_puzzle_state, null_position, "D");

    if (processed_states.find(hash) == processed_states.end()) {
      processed_states.insert(hash);
      next_states.push(PuzzleState(hash, current_puzzle_state.GetWay() + "U", current_puzzle_state.GetDistanation() + 1, field_size));
    }
  }
  if ((null_position + 1) % 4 != 0) {
    unsigned long long hash = current_puzzle_state.NextState(current_puzzle_state, null_position, "R");

    if (processed_states.find(hash) == processed_states.end()) {
      processed_states.insert(hash);
      next_states.push(PuzzleState(hash, current_puzzle_state.GetWay() + "L", current_puzzle_state.GetDistanation() + 1, field_size));
    }
  }
  if (null_position % 4 != 0) {
    unsigned long long hash = current_puzzle_state.NextState(current_puzzle_state, null_position, "L");

    if (processed_states.find(hash) == processed_states.end()) {
      processed_states.insert(hash);
      next_states.push(PuzzleState(hash, current_puzzle_state.GetWay() + "R", current_puzzle_state.GetDistanation() + 1, field_size));
    }
  }
}

PuzzleSolution FindShortestWayToSolvePuzzle(unsigned long long starting_state, int field_size) {
  std::priority_queue<PuzzleState> next_states;
  std::set<unsigned long long> processed_states;
  PuzzleState puzzle_state(starting_state, "", 0, field_size);

  if (!HasSolution(puzzle_state)) {
    return PuzzleSolution(-1, "", 0, 0);
  }

  next_states.push(puzzle_state);
  processed_states.insert(starting_state);

  while (!next_states.empty()) {
    PuzzleState current_puzzle_state = next_states.top();

    next_states.pop();

    if (current_puzzle_state.GetInformation().null_position == 1311768467463790320) {
      return current_puzzle_state.GetInformation();
    }

    if (current_puzzle_state.GetDistanation() + current_puzzle_state.GetPossibleDistanation() > 80) {
      continue;
    }

    FindNextPuzzleStates(current_puzzle_state, processed_states, next_states);
  }
  return PuzzleSolution(-1, "", 0, 0);
}

int main() {
  int field_size = 4;
  unsigned long long my_hash = 0;

  for (int i = 0; i < field_size*field_size; ++i) {
    unsigned long long value = 0;
    std::cin >> value;
    my_hash = (my_hash << field_size) + value;
  }

  PuzzleSolution answer = FindShortestWayToSolvePuzzle(my_hash, field_size);

  if (answer.null_position != -1) {
    std::cout << answer.distance_ << "\n";
    std::cout << answer.way_;
  }
  else {
    std::cout << -1;
  }

  return 0;
}