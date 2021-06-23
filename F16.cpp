#include "F16.h"
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

BoolMatrix::BoolMatrix(int n) {
  size = n;
  std::vector<bool> v(size, 0);
  for (int i = 0; i < size; ++i) {
    matrix.push_back(v);
  }
}

BoolMatrix::BoolMatrix(std::vector<std::vector<bool>> &matr) {
  size = matr.size();
  matrix = matr;
}

bool BoolMatrix::operator==(const BoolMatrix &other) const {
  return (matrix == other.matrix && size == other.size);
}

BoolMatrix BoolMatrix::operator+(const BoolMatrix &other) const {
  BoolMatrix result(size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      result.matrix[i][j] = matrix[i][j] || other.matrix[i][j];
    }
  }
  return result;
}

BoolMatrix BoolMatrix::operator*(const BoolMatrix &other) const {
  BoolMatrix result(size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      for (int k = 0; k < size; ++k) {
        if (this->matrix[i][k] && other.matrix[k][j]) {
          result.matrix[i][j] = true;
        }
      }
    }
  }
  return result;
}

BoolMatrix BoolMatrix::locking() const {
  BoolMatrix result = *this;
  for (int vertex = 0; vertex < size; ++vertex) {
    std::vector<int> used(size);
    std::queue<int> bfs_from_vertex;
    bfs_from_vertex.push(vertex);
    used[vertex] = 1;
    while (bfs_from_vertex.size() != 0) {
      int current_vertex = bfs_from_vertex.front();
      bfs_from_vertex.pop();
      result.matrix[vertex][current_vertex] = 1;
      for (int neighbor = 0; neighbor < size; ++neighbor) {
        if (used[neighbor] == 0 && matrix[current_vertex][neighbor] == 1) {
          used[neighbor] = 1;
          bfs_from_vertex.push(neighbor);
        }
      }
    }
  }
  return result;
}

/// <summary>
/// //////////////////////////////////////////// end of Matrix
/// //////////////////////////////////////////// begin of DynamicState
/// </summary>

DynamicState::DynamicState(char symbol, const std::string &str) {
  int size = str.size() + 1;
  Whole = BoolMatrix(size);
  Prefix = BoolMatrix(size);
  Suffix = BoolMatrix(size);
  Middle = BoolMatrix(size);
  for (int i = 0; i < size; ++i) {
    Prefix.matrix[i][i] = 1;
    Suffix.matrix[i][i] = 1;
    Middle.matrix[i][i] = 1;
  }
  if (symbol == '1') {
    for (int i = 0; i < size; ++i) {
      Whole.matrix[i][i] = 1;
    }
  } else {
    for (int i = 0; i < size - 1; ++i) {
      if (str[i] == symbol) {
        Middle.matrix[i][i + 1] = 1;
        Prefix.matrix[i][i + 1] = 1;
        Suffix.matrix[i][i + 1] = 1;
        Whole.matrix[i][i + 1] = 1;
      }
    }
  }
}

DynamicState DynamicState::operator+(const DynamicState &other) const {
  DynamicState result;
  result.Whole = Whole + other.Whole;
  result.Prefix = Prefix + other.Prefix;
  result.Suffix = Suffix + other.Suffix;
  result.Middle = Middle + other.Middle;
  return result;
}

DynamicState DynamicState::operator*(const DynamicState &other) const {
  DynamicState result;
  result.Whole = Whole * other.Whole;
  result.Prefix =
      Whole * other.Prefix + Prefix; // w = a.w * b.w, p = a.w * b.p + a.p,
  result.Suffix = Suffix * other.Whole +
                  other.Suffix; // s = a.s * b.w + b.s, ss = a.s * b.p.
  result.Middle = Suffix * other.Prefix + Middle + other.Middle;
  return result;
}

DynamicState DynamicState::star() const {
  DynamicState result;
  result.Whole = Whole.locking();
  result.Prefix = result.Whole * Prefix; // a.w + E, p = w*a.p + E,
  result.Suffix = Suffix * result.Whole; // s = a.s*w + E, ss = a.s*w*a.p + E
  result.Middle = Suffix * result.Whole * Prefix + Middle;
  return result;
}

const BoolMatrix &DynamicState::GetMiddle() const { return Middle; }
const BoolMatrix &DynamicState::GetWhole() const { return Whole; }
const BoolMatrix &DynamicState::GetPrefix() const { return Prefix; }
const BoolMatrix &DynamicState::GetSuffix() const { return Suffix; }

/// /////////////////////////////////////////////////// end of DynamicState
int Solution(const std::string &formal_expression, const std::string &word) {
  int expression_size = formal_expression.size();
  int word_size = word.size();
  std::stack<DynamicState> Polish_Writing;
  for (int i = 0; i < expression_size; ++i) {
    if ((formal_expression[i] - 'a' >= 0 && formal_expression[i] - 'c' <= 0) ||
        formal_expression[i] == '1') {
      Polish_Writing.push(DynamicState(formal_expression[i], word));
    } else {
      if (Polish_Writing.empty()) {
        throw std::runtime_error("Uncorrect input");
      }
      DynamicState second = Polish_Writing.top();
      Polish_Writing.pop();
      if (formal_expression[i] == '*') {
        Polish_Writing.push(second.star());
      } else {
        if (Polish_Writing.empty()) {
          throw std::runtime_error("Uncorrect input");
        }
        DynamicState first = Polish_Writing.top();
        Polish_Writing.pop();
        if (formal_expression[i] == '+') {
          Polish_Writing.push(first + second);
        } else {
          if (formal_expression[i] == '.') {
            Polish_Writing.push(first * second);
          } else {
            throw std::runtime_error("Uncorrect input");
          }
        }
      }
    }
  }
  if (Polish_Writing.size() != 1)
    throw std::runtime_error("Uncorrect input");
  DynamicState answer = Polish_Writing.top();

  int max_word_length = 0;
  for (int left_end = 0; left_end < word_size + 1; left_end++) {
    for (int right_end = 0; right_end < word_size + 1; ++right_end) {
      int word_length = right_end - left_end;
      if (answer.GetMiddle().matrix[left_end][right_end] &&
          max_word_length < word_length) {
        max_word_length = word_length;
      }
    }
  }
  return max_word_length;
}
