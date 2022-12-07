#include <iostream>

int main () {
  int a {12};
  int b{};
  b = ( a >> 1);
  std::cout << b << std::endl;
  
  int d = 1;
  d = (d << 3);
  std::cout << d << "_" << ~ d << std::endl;

  int c {0};
  for (int i = 0; i < 5; i ++) {
    c = (c >> 1);
    std::cout << c << std::endl;
  }  
  return 0;
}

