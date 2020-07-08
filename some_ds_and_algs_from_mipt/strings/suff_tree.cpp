#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T = std::string, typename S = long long,
          typename C = std::vector<S>>
class SuffixArray {
 public:
  friend class SuffixTree;

  SuffixArray(T& str) : str_len(str.size()), str_(str) {
    SortOfSuffixesOfCyclicString();
  };

  C& GetSuffixArray() { return suffix_array; }

  void BuildLCP();

  S Size() const { return suffix_array.size(); }

  S LCP(S i) const { return lcp[i]; }

  S operator[](S i) const { return suffix_array[i]; }

  void ModifyLCP() {
    modified_lcp = lcp;
    modified_lcp.pop_back();
    modified_lcp.insert(modified_lcp.begin(), -1);
    lcp = modified_lcp;
  }

  void Show() {
    for (auto elem : lcp) {
      std::cout << elem << " ";
    }

    std::cout << std::endl;
  }

 private:
  void ZeroPhase(C& count, C& classes_0, C& permutations_0);

  void IPhaze(int phaze, C& count, C& classes_0, C& permutations_0,
              C& classes_n, C& permutations_n);

  void SortOfSuffixesOfCyclicString();

  S classes_count = 1;
  const S alphabet = 200002;

  const S str_len;
  const T str_;

  C suffix_array;
  C lcp;
  C modified_lcp;
};

struct Node {
  Node() {
    parent = nullptr;
    depth = 0;
  }

  Node(Node* parent, long long depth) : parent(parent), depth(depth) {}

  Node* parent;
  long long depth;
  long long key;
  short int str;
  long long start;
  long long end;
  long long max_depth = -1;
  std::vector<Node*> children;
};

class SuffixTree {
 public:
  SuffixTree(const SuffixArray<>& suffix_array, const long long str1_lenght)
      : root(new Node(nullptr, 0)), size(0), str_size(suffix_array.str_len) {
    Node* previous = root;
    AddNextSuffix(root, 1, 0);

    for (long long i = 1; i < suffix_array.str_len; ++i) {
      previous = AddNextSuffix(
          previous, suffix_array.str_len - suffix_array.suffix_array[i],
          suffix_array.lcp[i]);
    }

    FindMaxDepth(root);
    DefineBorders(root, str1_lenght);
  }

  void Show() {
    std::cout << size << std::endl;
    ShowTree(root);
  }

  Node* GetRoot() { return root; }

 private:
  void ShowTree(Node* curr) {
    for (auto child : curr->children) {
      printf("%d %d %d %d\n", child->parent->key, child->str, child->start,
             child->end);
      ShowTree(child);
    }
  }

  void DefineBorders(Node* curr, const int str1_lenght) {
    if (curr->parent != nullptr) {
      curr->start = str_size - curr->max_depth + curr->parent->depth;
      curr->str = curr->start < str1_lenght ? 0 : 1;

      if (curr->str == 1) {
        curr->start -= str1_lenght;
      }
      curr->end = curr->start + curr->depth - curr->parent->depth;

      if (curr->str == 0) {
        curr->end = std::min((long long)str1_lenght, curr->end);
      }
    }

    for (auto& child : curr->children) {
      DefineBorders(child, str1_lenght);
    }

    return;
  }

  void FindMaxDepth(Node* curr) {
    curr->key = size;
    ++size;

    if (!curr->children.empty()) {
      for (auto child : curr->children) {
        FindMaxDepth(child);
        curr->max_depth = std::max(child->max_depth, curr->max_depth);
      }
    } else {
      curr->max_depth = curr->depth;
      curr->parent->max_depth = std::max(curr->parent->max_depth, curr->depth);
    }
  }

  Node* AddNextSuffix(Node*& vertex, const long long depth,
                      const long long lcp) {
    if (vertex->depth == 0 || vertex->depth == lcp) {
      Node* added = new Node(vertex, depth);

      vertex->children.push_back(added);
      return added;
    } else if (vertex->parent->depth < lcp) {
      Node* inserted = new Node(vertex->parent, lcp);

      vertex->parent->children.pop_back();
      vertex->parent->children.push_back(inserted);
      inserted->children.push_back(vertex);
      vertex->parent = inserted;
    }
    return AddNextSuffix(vertex->parent, depth, lcp);
  }

  Node* root;
  long long size;
  long long str_size;
};

int main() {
  std::string str1, str2;

  std::cin >> str1 >> str2;

  long long len_1 = str1.length();

  str1 = str1 + str2;

  SuffixArray<> suff_arr(str1);

  suff_arr.BuildLCP();
  suff_arr.ModifyLCP();

  SuffixTree suff_tree(suff_arr, len_1);
  suff_tree.Show();

  return 0;
}

template <typename T, typename S, typename C>
inline void SuffixArray<T, S, C>::BuildLCP() {
  S pos = 0;
  S length = str_.length();
  lcp = std::vector<S>(length);
  std::vector<S> reverse(length);

  for (S i = 0; i < length; ++i) {
    reverse[suffix_array[i]] = i;
  }

  for (S i = 0; i < length; ++i) {
    if (pos > 0) {
      --pos;
    }
    if (reverse[i] == length - 1) {
      lcp[length - 1] = -1;
      pos = 0;
    } else {
      S next = suffix_array[reverse[i] + 1];

      while (std::max(i + pos, next + pos) < length &&
             str_[i + pos] == str_[next + pos]) {
        ++pos;
      }
      lcp[reverse[i]] = pos;
    }
  }
}

template <typename T, typename S, typename C>
inline void SuffixArray<T, S, C>::ZeroPhase(C& count, C& classes_0,
                                            C& permutations_0) {
  for (S i = 0; i < str_len; ++i) {
    ++count[str_[i]];
  }

  for (S i = 1; i < alphabet; ++i) {
    count[i] += count[i - 1];
  }
  for (S i = 0; i < str_len; ++i) {
    permutations_0[--count[str_[i]]] = i;
  }

  classes_0[permutations_0[0]] = 0;

  for (S i = 1; i < str_len; ++i) {
    if (str_[permutations_0[i]] != str_[permutations_0[i - 1]]) {
      ++classes_count;
    }

    classes_0[permutations_0[i]] = classes_count - 1;
  }

  return;
}

template <typename T, typename S, typename C>
inline void SuffixArray<T, S, C>::IPhaze(int phaze, C& count, C& classes_0,
                                         C& permutations_0, C& classes_n,
                                         C& permutations_n) {
  for (S i = 0; i < str_len; ++i) {
    permutations_n[i] = permutations_0[i] - (1 << phaze);

    if (permutations_n[i] < 0) {
      permutations_n[i] += str_len;
    }
  }

  for (S i = 0; i < alphabet; ++i) {
    count[i] = 0;
  }

  for (S i = 0; i < str_len; ++i) {
    ++count[classes_0[permutations_n[i]]];
  }
  for (S i = 1; i < classes_count; ++i) {
    count[i] += count[i - 1];
  }
  for (S i = str_len - 1; i >= 0; --i) {
    permutations_0[--count[classes_0[permutations_n[i]]]] = permutations_n[i];
  }

  classes_n[permutations_0[0]] = 0;
  classes_count = 1;

  for (S i = 1; i < str_len; ++i) {
    S mid1 = (permutations_0[i] + (1 << phaze)) % str_len;
    S mid2 = (permutations_0[i - 1] + (1 << phaze)) % str_len;

    if (classes_0[permutations_0[i]] != classes_0[permutations_0[i - 1]] ||
        classes_0[mid1] != classes_0[mid2]) {
      ++classes_count;
    }

    classes_n[permutations_0[i]] = classes_count - 1;
  }

  classes_0 = classes_n;
}

template <typename T, typename S, typename C>
inline void SuffixArray<T, S, C>::SortOfSuffixesOfCyclicString() {
  C count(alphabet, 0);
  C classes_0(str_len);
  C permutations_0(str_len);
  C classes_n(str_len);
  C permutations_n(str_len);

  ZeroPhase(count, classes_0, permutations_0);

  for (S phaze = 0; (1 << phaze) < str_len; ++phaze) {
    IPhaze(phaze, count, classes_0, permutations_0, classes_n, permutations_n);
  }

  suffix_array = permutations_0;
}
