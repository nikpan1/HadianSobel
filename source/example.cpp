#include <iostream>
#include "Array.hpp"
#include "TournamentTree.hpp"
using namespace std;

int main() {
  
  for (int i = 2; i <= 50000; i = i + 2) {
    auto q = NewRandomArray(i);
    HadianSobel(&q, i / 2);
  }
  return 0;
}
