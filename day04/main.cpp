#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define INPUT "input.txt"
#define TEST "test.txt"

int main() {
  std::ifstream file(TEST);
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
  std::map<int32_t, std::vector<int32_t>> commonElementsMap;
  int32_t cardIndex = 1;
  for (auto &line : text) {
    auto pipe_position = std::find(line.begin(), line.end(), '|');

    std::string left_side(line.begin(), pipe_position);
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

  /* std::cout << res << std::endl; */

  std::cout << "Common Eements for each card" << std::endl;
  for (const auto [k, v] : commonElementsMap) {
    std::cout << "Key: " << k << '\n';
    std::cout << "\t\t";
    for (const auto &e : v) {
      std::cout << e << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  return 0;
}
