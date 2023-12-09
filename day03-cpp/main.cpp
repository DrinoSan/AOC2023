#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define TEST "test.txt"
#define INPUT "input.txt"

class PartNumber {
public:
  PartNumber(int32_t num, int32_t x, int32_t y, int32_t width)
      : num{num}, x{x}, y{y}, width{width} {}
  ~PartNumber() = default;

  int32_t num;
  int32_t x;
  int32_t y;
  int32_t width;
};

class Symbol {
public:
  Symbol(char c, int32_t x, int32_t y) : c{c}, x{x}, y{y} {}
  ~Symbol() = default;

  char c;
  int32_t x;
  int32_t y;

  bool isAdjecentTo(const PartNumber &partNumber) const {
    if (partNumber.y >= this->y + 2) {
      return false;
    }

    if (partNumber.y <= this->y - 2) {
      return false;
    }

    for (int32_t i = partNumber.x + 1; i < partNumber.x + partNumber.width + 1;
         ++i) {
      if (this->x == std::clamp(this->x, partNumber.x, i)) {
        return true;
      }
    }

    for (int32_t i = partNumber.x + 1; i < partNumber.x + partNumber.width + 1;
         ++i) {
      if (this->x == std::clamp(this->x, partNumber.x - 1, i)) {
        return true;
      }
    }

    return false;
  }
};

int main() {
  std::ifstream file(INPUT);
  std::vector<std::vector<char>> map2D;
  std::vector<PartNumber> partNumbers;
  std::vector<Symbol> symbols;

  std::string str;
  while (getline(file, str)) {
    map2D.push_back(std::move(std::vector<char>(str.begin(), str.end())));
  }

  for (int32_t line_idx = 0; line_idx < map2D.size(); ++line_idx) {
    /* std::string_view sv(map2D[line_idx].data(), map2D[line_idx].size()); */
    auto &line = map2D[line_idx];

    for (int32_t char_idx = 0; char_idx < line.size(); ++char_idx) {
      if (std::isdigit(line[char_idx])) {
        std::string tmpNum;
        while (std::isdigit(line[char_idx])) {
          tmpNum += line[char_idx++];
        }

        partNumbers.push_back(
            std::move(PartNumber(std::stoi(tmpNum), char_idx - tmpNum.size(),
                                 line_idx, tmpNum.size())));
      } if (line[char_idx] == '*') {
        symbols.push_back(
            std::move(Symbol(line[char_idx], char_idx, line_idx)));
      }
    }
  }

  int32_t result;
  for (const auto &symbol : symbols) {
    std::vector<int32_t> pairs;
    for (const auto &partNumber : partNumbers) {
      if (symbol.isAdjecentTo(partNumber)) {
        pairs.push_back(partNumber.num);
      }
    }

    if (pairs.size() == 2) {
      result += pairs[0] * pairs[1];
    }
  }
  std::cout << "Result: " << result << std::endl;

  return 0;
}
