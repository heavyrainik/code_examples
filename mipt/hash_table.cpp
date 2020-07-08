#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::shared_ptr;
using std::vector;

struct DataBlock {
  DataBlock(std::string new_value) { value = new_value; }

  std::string value = "";
  bool is_deleted = false;
};

class HashTable {
public:
  HashTable() { table.assign(capacity_, nullptr); }

  bool Add(std::string new_value) {
    if (Search(new_value)) {
      return false;
    }

    int hash = Hash(new_value);
    int hash2 = Hash2(new_value);

    for (size_t i = 0; i < capacity_; ++i) {
      if (table[hash] == nullptr) {
        table[hash] = std::make_shared<DataBlock>(new_value);

        current_size_++;

        if (static_cast<float>(current_size_ )/static_cast<float>( capacity_)>=oversize_coefficient_) {
          Resize();
        }

        return true;
      } else if (table[hash]->is_deleted) {
        table[hash]->is_deleted = false;
        table[hash]->value = new_value;

        current_size_++;

        return true;
      }

      hash = (hash + i * hash2) % capacity_;
    }
  }

  bool Delete(std::string value) {
    if (!Search(value)) {
      return false;
    }

    int hash = Hash(value);
    int hash2 = Hash2(value);

    for (int i = 0; i < capacity_; ++i) {
      if (table[hash]->value == value) {
        table[hash]->is_deleted = true;
        current_size_--;

        return true;
      }

      hash = (hash + i * hash2) % capacity_;
    }
  }

  bool Search(std::string value) {
    int hash = Hash(value);
    int hash2 = Hash2(value);

    for (size_t i = 0; i < capacity_; ++i) {
      if (table[hash] != nullptr) {
        if (table[hash]->value == value) {
          return !(table[hash]->is_deleted);
        }
      }
      else {
        return false;
      }

      hash = (hash + hash2 * i) % capacity_;
    }

    return false;
  }

private:
  void Resize() {
    std::vector<shared_ptr<DataBlock>> old_table = table;

    capacity_ *= 2;
    current_size_ = 0;

    table.assign(capacity_, nullptr);

    for (size_t i = 0; i < capacity_ / 2; ++i) {
      if (old_table[i] && !old_table[i]->is_deleted) {
        Add(old_table[i]->value);
      }
    }
  }

  int Hash2(std::string value) { return int(value[0] % capacity_) * 2 + 1; }

  int Hash(std::string value) {
    int prime_number = 1;
    int hash = 0;

    for (int i = 0; i < value.size(); ++i) {
      hash = (hash * prime_number + int(value[i])) % capacity_;
    }

    return hash;
  }

  size_t capacity_ = 8;
  size_t current_size_ = 0;
  double oversize_coefficient_ = 0.75;

  vector<shared_ptr<DataBlock>> table;
};

int main() {
  shared_ptr<HashTable> hash_table = std::make_shared<HashTable>();

  char command = '-';
  std::string value = "";
  bool is_successful = true;

  while (std::cin >> command) {
    std::cin >> value;

    if (command == '+') {
      is_successful = hash_table->Add(value);
    }
    else if (command == '-') {
      is_successful = hash_table->Delete(value);
    }
    else {
      is_successful = hash_table->Search(value);
    }

    if (is_successful) {
      std::cout << "OK" << std::endl;
    } else {
      std::cout << "FAIL" << std::endl;
    }
  }

  return 0;
}

