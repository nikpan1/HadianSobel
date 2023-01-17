#include <iostream>
#include "Array.hpp"
#include "TournamentTree.hpp"
using namespace std;

int main() {
  auto q = NewRandomArray(10);
  
  //printArray(&q);
  HadianSobel(&q, 5);

  return 0;
}
