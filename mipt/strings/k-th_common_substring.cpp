#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T = std::string, typename C = std::vector<int>>
class SuffixArray {
 public:
  SuffixArray(T& str) : str_len(str.size()), str_(str) {
    SortOfSuffixesOfCyclicString();
  };

  C& GetSuffixArray() { return suffix_array; }

  void BuildLCP() {
    long long pos = 0;
    long long length = str_.length();
    lcp = std::vector<int>(length);
    std::vector<int> reverse(length);

    for (long long i = 0; i < length; ++i) {
      reverse[suffix_array[i]] = i;
    }

    for (long long i = 0; i < length; ++i) {
      if (pos > 0) {
        --pos;
      }
      if (reverse[i] == length - 1) {
        lcp[length - 1] = -1;
        pos = 0;
      } else {
        long long next = suffix_array[reverse[i] + 1];

        while (std::max(i + pos, next + pos) < length &&
               str_[i + pos] == str_[next + pos]) {
          ++pos;
        }
        lcp[reverse[i]] = pos;
      }
    }
  }

  long long Size() const { return suffix_array.size(); }

  int LCP(int i) const { return lcp[i]; }

  int operator[](int i) const { return suffix_array[i]; }

 private:
  void ZeroPhase(C& count, C& classes_0, C& permutations_0) {
    for (long long i = 0; i < str_len; ++i) {
      ++count[str_[i]];
    }

    for (long long i = 1; i < alphabet; ++i) {
      count[i] += count[i - 1];
    }
    for (long long i = 0; i < str_len; ++i) {
      permutations_0[--count[str_[i]]] = i;
    }

    classes_0[permutations_0[0]] = 0;

    for (long long i = 1; i < str_len; ++i) {
      if (str_[permutations_0[i]] != str_[permutations_0[i - 1]]) {
        ++classes_count;
      }

      classes_0[permutations_0[i]] = classes_count - 1;
    }

    return;
  }

  void IPhaze(int phaze, C& count, C& classes_0, C& permutations_0,
              C& classes_n, C& permutations_n) {
    for (long long i = 0; i < str_len; ++i) {
      permutations_n[i] = permutations_0[i] - (1 << phaze);

      if (permutations_n[i] < 0) {
        permutations_n[i] += str_len;
      }
    }

    for (long long i = 0; i < alphabet; ++i) {
      count[i] = 0;
    }

    for (long long i = 0; i < str_len; ++i) {
      ++count[classes_0[permutations_n[i]]];
    }
    for (long long i = 1; i < classes_count; ++i) {
      count[i] += count[i - 1];
    }
    for (int i = str_len - 1; i >= 0; --i) {
      permutations_0[--count[classes_0[permutations_n[i]]]] = permutations_n[i];
    }

    classes_n[permutations_0[0]] = 0;
    classes_count = 1;

    for (long long i = 1; i < str_len; ++i) {
      long long mid1 = (permutations_0[i] + (1 << phaze)) % str_len;
      long long mid2 = (permutations_0[i - 1] + (1 << phaze)) % str_len;

      if (classes_0[permutations_0[i]] != classes_0[permutations_0[i - 1]] ||
          classes_0[mid1] != classes_0[mid2]) {
        ++classes_count;
      }

      classes_n[permutations_0[i]] = classes_count - 1;
    }

    classes_0 = classes_n;
  }

  void SortOfSuffixesOfCyclicString() {
    C count(alphabet, 0);
    C classes_0(str_len);
    C permutations_0(str_len);
    C classes_n(str_len);
    C permutations_n(str_len);

    ZeroPhase(count, classes_0, permutations_0);

    for (int phaze = 0; (1 << phaze) < str_len; ++phaze) {
      IPhaze(phaze, count, classes_0, permutations_0, classes_n,
             permutations_n);
    }

    suffix_array = permutations_0;
  }

  long long classes_count = 1;
  const int alphabet = 200002;

  const long long str_len;
  const T str_;

  C suffix_array;
  C lcp;
};

std::string KOrderSubstring(long long order, int str1, const std::string& text,
                            const SuffixArray<>& suffix_array) {
  long long counter = 0;
  int current_min = text.length();
  long long str_num_cur = 0;
  long long str_num_prev = 0;

  long long suffix_arrar_size = suffix_array.Size();

  if (suffix_array[0] > str1) {
    str_num_prev = 2;
  } else {
    str_num_prev = 1;
  }

  for (long long i = 1; i < suffix_arrar_size; ++i) {
    if (suffix_array[i] > str1) {
      str_num_cur = 2;
    } else {
      str_num_cur = 1;
    }

    if (str_num_cur != str_num_prev) {
      counter += std::max(0, suffix_array.LCP(i - 1) - current_min);
      current_min = suffix_array.LCP(i - 1);
    } else {
      current_min = std::min(current_min, suffix_array.LCP(i - 1));
    }

    str_num_prev = str_num_cur;

    if (counter >= order) {
      long long difference = counter - order;
      long long distance = suffix_array.LCP(i - 1) - difference;
      std::string ans = "";

      for (long long j = suffix_array[i]; j < suffix_array[i] + distance; ++j) {
        ans += text[j];
      }

      return ans;
    }
  }

  return "-1";
}

int main() {
  std::string str1, str2;
  long long order;

  std::cin >> str1 >> str2 >> order;

  long long len_1 = str1.length();

  str1 = str1 + '$' + str2 + '#';

  SuffixArray<> suff_arr(str1);

  suff_arr.BuildLCP();

  std::cout << KOrderSubstring(order, len_1, str1, suff_arr);
}
