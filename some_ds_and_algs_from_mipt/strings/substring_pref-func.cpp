#include <iostream>
#include <string>
#include <vector>

void FindSubstringEntries(std::string t, int n) {
  int text_lenght = t.length();
  std::vector<int> prefixes(text_lenght, 0);

  for (int i = 1; i < text_lenght; ++i) {
    int j = prefixes[i - 1];

    while (j > 0 && t[i] != t[j]) {
      j = prefixes[j - 1];
    }

    if (t[i] == t[j]) {
      ++j;
    }

    prefixes[i] = j;

    if (j == n) {
      std::cout << i - 2 * n << " ";
    }
  }
}

int main() {
  std::string t;
  std::string s;

  std::cin >> s >> t;

  FindSubstringEntries(s + "#" + t, s.length());

  return 0;
}
