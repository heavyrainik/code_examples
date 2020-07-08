#include <algorithm>
#include <iostream>
#include <vector>

void SubstringSearch(const std::string& text, int pattern_length, std::vector <int>& answer) {
  std::vector <int> z_function(pattern_length, 0);
  int left = 0;
  int right = 0;

  for (int i = 1; i < text.length(); i++) {
    int current_z_func_res = 0;

    if (i - left > pattern_length) {
      current_z_func_res = std::max(0, right - i);
    } else {
      current_z_func_res = std::max(0, std::min(right - i, z_function[i - left]));
    }

    while (i + current_z_func_res < text.length() && text[current_z_func_res] == text[i + current_z_func_res]) {
      current_z_func_res++;
    }

    if (i < pattern_length) {
      z_function[i] = current_z_func_res;
    }

    if (i + current_z_func_res - 1 > right) {
      left = i;
      right = i + current_z_func_res - 1;
    }

    if (current_z_func_res == pattern_length) {
      answer.push_back(i - pattern_length - 1);
    }
  }
}

int main() {
  std::string pattern, text;
  std::cin >> pattern >> text;

  std::vector <int> answer;
  SubstringSearch(pattern + '#' + text, pattern.length(), answer);

  for (auto a : answer) {
    std::cout << a << " ";
  }
}