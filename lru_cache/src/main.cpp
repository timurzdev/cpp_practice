#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

class lru_cache {
  size_t size_;
  std::unordered_map<std::string, int> data_;
  std::list<std::string> order_;

public:
  lru_cache(size_t size) : size_(size), data_(), order_() {
    data_.reserve(size);
  };

  void add(std::string key, int value) {
    if (data_.size() > size_) {
      return;
    }

    data_[key] = value;
    order_.push_back(key);
  };

  size_t size() { return size_; }
};

int main() {
  lru_cache cache(1);
  cache.add("some_key", 10);
  std::cout << "size: " << cache.size() << std::endl;
  cache.add("some_key_1", 11);
  std::cout << "size: " << cache.size() << std::endl;
}
