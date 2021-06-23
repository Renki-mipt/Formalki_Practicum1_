#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

struct BoolMatrix {
public:
  BoolMatrix() {}
  BoolMatrix(int n);
  BoolMatrix(std::vector<std::vector<bool>> &matr);
  bool operator==(const BoolMatrix &other) const;
  BoolMatrix operator+(const BoolMatrix &other) const;
  BoolMatrix operator*(const BoolMatrix &other) const;
  BoolMatrix locking() const; // замыкание графа, заданного матрицей смежностей
  std::vector<std::vector<bool>> matrix;
  int size;
};

class DynamicState {
public:
  DynamicState(){};
  DynamicState(char symbol, const std::string &str);
  DynamicState operator+(const DynamicState &other) const;
  DynamicState operator*(const DynamicState &other) const;
  DynamicState star() const;
  const BoolMatrix &GetMiddle() const;
  const BoolMatrix &GetWhole() const;
  const BoolMatrix &GetPrefix() const;
  const BoolMatrix &GetSuffix() const;

private:
  BoolMatrix Whole; // является ли подслово словом языка
  BoolMatrix Prefix; // является ли подслово префиксом слова языка
  BoolMatrix Suffix; // является ли подслово суффиксом слова языка
  BoolMatrix Middle; // является ли подсловом слова языка
};

int Solution(const std::string &formal_expression, const std::string &word);
