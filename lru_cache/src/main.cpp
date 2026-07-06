#include <iostream>
#include <list>
#include <map>
#include <string>
#include <unordered_map>

class lru_cache {
  size_t size_;
  std::unordered_map<std::string, int> data_;
  std::list<std::string> order_;

  void add_(std::string key, int value) {
    auto it = data_.find(key);
    if (it != data_.end()) {
      // element found
      data_[key] = value;
      // popup list node
      touch_(key);
      return;
    }
    data_[key] = value;
    order_.push_back(key);
  };

  void touch_(std::string key) {
    order_.remove(key);
    order_.push_back(key);
  }

public:
  lru_cache(size_t size) : size_(size), data_(), order_() {
    data_.reserve(size);
  };

  void add(std::string key, int value) {
    if (data_.size() >= size_) {
      // pop lru
      auto front = order_.front();
      order_.pop_front();
      add_(key, value);
      return;
    }
  };

  int get(std::string key) {
    if (auto it = data_.find(key); it != data_.end()) {
      touch_(key);
      return it->second;
    }

    return 0;
  };

  void print_order() {
    std::cout << "order_ size: " << order_.size() << std::endl;
    for (auto i : order_) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }

  size_t size() { return size_; }
};

int main() {
  lru_cache cache(3);
  std::map<std::string, int> testcase{
      {"key1", 1},
      {"key2", 2},
      {"key1", 3},
  };

  for (auto pair_ : testcase) {
    cache.add(pair_.first, pair_.second);
    std::cout << "size: " << cache.size() << std::endl;
    std::cout << "adding key: " << pair_.first << " value: " << pair_.second
              << std::endl;
    cache.print_order();
  };
}
