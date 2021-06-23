#include "F16.h"

int main() {
  std::string F, U;
  std::cin >> F >> U;
  try {
    std::cout << Solution(F, U) << '\n';
  } catch (std::exception &s) {
    std::cout << s.what() << '\n';
  }
  return 0;
}
