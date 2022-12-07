#include <iostream>

int main () {
  int a = 0;
  int b = 0;
  b = a++;
  std::cout << b;
  b = ++a;
  std::cout << b;
 
  return 0;
}

