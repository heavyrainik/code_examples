#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T = std::string, typename C = std::vector<int>>
class SuffixArray {
public:
  explicit SuffixArray(const T& str) : str_len_(str.size()), str_(str) {
    SortOfSuffixesOfCyclicString();
  };

  C& GetSuffixArray() { return suffix_array_; }

  std::vector<int> BuildSuffixLCP() {
    int pos = 0;
    int length = str_.length();
    std::vector<int> lcp(length);
    std::vector<int> reverse(length);

    for (int i = 0; i < length; ++i) {
      reverse[suffix_array_[i]] = i;
    }

    for (int i = 0; i < length; ++i) {
      if (pos > 0) {
        --pos;
      }
      if (reverse[i] == length - 1) {
        lcp[length - 1] = -1;
        pos = 0;
      }
      else {
        int next = suffix_array_[reverse[i] + 1];

        while (std::max(i + pos, next + pos) < length &&
          str_[i + pos] == str_[next + pos]) {
          ++pos;
        }
        lcp[reverse[i]] = pos;
      }
    }

    return lcp;
  }

private:
  void ZeroPhase(C& count, C& classes_0, C& permutations_0) {
    for (int i = 0; i < str_len_; ++i) {
      ++count[str_[i]];
    }

    for (int i = 1; i < alphabet_; ++i) {
      count[i] += count[i - 1];
    }
    for (int i = 0; i < str_len_; ++i) {
      permutations_0[--count[str_[i]]] = i;
    }

    classes_0[permutations_0[0]] = 0;

    for (int i = 1; i < str_len_; ++i) {
      if (str_[permutations_0[i]] != str_[permutations_0[i - 1]]) {
        ++classes_count_;
      }

      classes_0[permutations_0[i]] = classes_count_ - 1;
    }

    return;
  }

  void IPhaze(const int phaze, C& count, C& classes_0, C& permutations_0,
    C& classes_n, C& permutations_n) {
    for (int i = 0; i < str_len_; ++i) {
      permutations_n[i] = permutations_0[i] - (1 << phaze);

      if (permutations_n[i] < 0) {
        permutations_n[i] += str_len_;
      }
    }

    for (int i = 0; i < alphabet_; ++i) {
      count[i] = 0;
    }

    for (int i = 0; i < str_len_; ++i) {
      ++count[classes_0[permutations_n[i]]];
    }
    for (int i = 1; i < classes_count_; ++i) {
      count[i] += count[i - 1];
    }
    for (int i = str_len_ - 1; i >= 0; --i) {
      permutations_0[--count[classes_0[permutations_n[i]]]] = permutations_n[i];
    }

    classes_n[permutations_0[0]] = 0;
    classes_count_ = 1;

    for (int i = 1; i < str_len_; ++i) {
      int mid1 = (permutations_0[i] + (1 << phaze)) % str_len_;
      int mid2 = (permutations_0[i - 1] + (1 << phaze)) % str_len_;

      if (classes_0[permutations_0[i]] != classes_0[permutations_0[i - 1]] ||
        classes_0[mid1] != classes_0[mid2]) {
        ++classes_count_;
      }

      classes_n[permutations_0[i]] = classes_count_ - 1;
    }

    classes_0 = classes_n;
  }

  void SortOfSuffixesOfCyclicString() {
    C count(alphabet_, 0);
    C classes_0(str_len_);
    C permutations_0(str_len_);
    C classes_n(str_len_);
    C permutations_n(str_len_);

    ZeroPhase(count, classes_0, permutations_0);

    for (int phaze = 0; (1 << phaze) < str_len_; ++phaze) {
      IPhaze(phaze, count, classes_0, permutations_0, classes_n,
        permutations_n);
    }

    suffix_array_ = permutations_0;
  }

  int classes_count_ = 1;
  const int alphabet_ = 256;

  const int str_len_;
  const T str_;

  C suffix_array_;
};

int AmountOfUniqueSubstrings(const std::string& str,
  const std::vector<int>& suffix_array,
  const std::vector<int>& lcp) {
  int str_size = str.size();
  int amount = 0;

  for (int i = 0; i < str_size; ++i) {
    if (i != 0) {
      amount += (str_size - suffix_array[i] - 1);
    }
    if (i != str_size - 1) {
      amount -= lcp[i];
    }
  }

  return amount;
}

int main() {
  std::string str;

  std::cin >> str;
  str += "$";
  SuffixArray<> suf_arr(str);

  std::vector<int> suffix_array = suf_arr.GetSuffixArray();
  std::vector<int> lcp = suf_arr.BuildSuffixLCP();
  std::cout << AmountOfUniqueSubstrings(str, suffix_array, lcp);

  return 0;
}
