#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define INPUT "input.txt"
#define TEST "test.txt"

std::map<int32_t, std::vector<int32_t>> commonElementsMap;
std::map<int32_t, std::vector<int32_t>> result_trees;
std::vector<int32_t> result_tree_elements;

void createGraph(int32_t node) {
  std::vector<int32_t> nodes = commonElementsMap[node];
  for (const auto node_ : nodes) {
    result_tree_elements.push_back(node_);
    createGraph(node_);
  }
}

int main() {
  std::ifstream file(INPUT);
  std::vector<std::string> text;
  std::string prefix{"Card "};
  if (file.is_open()) {
    std::string line;
    int32_t idx = 1;
    while (std::getline(file, line)) {
      line.erase(0, prefix.size());
      line.erase(0, std::to_string(idx).size() + 2);
      text.push_back(line);
    }
  }

  int32_t res;
  int32_t cardIndex = 1;
  for (auto &line : text) {
    auto pipe_position = std::find(line.begin(), line.end(), '|');

    std::string left_side(line.begin() + 1, pipe_position);
    std::string right_side(pipe_position + 1, line.end());

    std::istringstream left_stream(left_side);
    std::istringstream right_stream(right_side);

    std::vector<int32_t> left_numbers{
        std::istream_iterator<int32_t>(left_stream),
        std::istream_iterator<int32_t>()};

    std::vector<int32_t> right_numbers{
        std::istream_iterator<int32_t>(right_stream),
        std::istream_iterator<int32_t>()};

    std::sort(left_numbers.begin(), left_numbers.end());
    std::sort(right_numbers.begin(), right_numbers.end());

    std::vector<int32_t> commonElementsVec;

    std::set_intersection(left_numbers.begin(), left_numbers.end(),
                          right_numbers.begin(), right_numbers.end(),
                          std::back_inserter(commonElementsVec));

    int32_t idx{1};
    for (auto &e : commonElementsVec) {
      e = cardIndex + idx++;
    }

    commonElementsMap[cardIndex++] = commonElementsVec;

    size_t equalCount = std::count_if(
        left_numbers.begin(), left_numbers.end(), [&](int32_t &num) {
          return std::find(right_numbers.begin(), right_numbers.end(), num) !=
                 right_numbers.end();
        });

    int32_t tmp = 0;
    for (int32_t i = 0; i < equalCount; ++i) {
      if (i > 0) {
        tmp *= 2;
      } else {
        tmp += 1;
      }
    }

    res += tmp;
  }

  std::cout << res << std::endl;

  for (const auto &[row_idx, values] : commonElementsMap) {
    createGraph(row_idx);
    result_trees[row_idx] = result_tree_elements;
    result_tree_elements.clear();
  }

  // Counting keys
  int keyCount = result_trees.size();

  // Counting elements in vectors
  int valueCount = 0;
  for (const auto &entry : result_trees) {
    const std::vector<int32_t> &values = entry.second;
    valueCount += values.size();
  }

  // Total count
  int totalCount = keyCount + valueCount;

  std::cout << "Number of keys: " << keyCount << std::endl;
  std::cout << "Number of elements in vectors: " << valueCount << std::endl;
  std::cout << "Total count: " << totalCount << std::endl;

  return 0;
}
