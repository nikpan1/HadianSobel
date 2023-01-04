#include <iostream>
#include "Array.hpp"
#include "BruteForce.hpp"
#include "TournamentTree.hpp"
using namespace std;


int main() {
  const int n = 10;
  const int k = 5;

  array arr, temp, t;
  vector<node> tree;
  for(int i = 1; i <= 100; i ++) {
    arr = NewRandomArray(n);
    printArray(&arr);
    temp = {arr.l, short(n - k + 1)};   
    tree = Construct(&temp);
    t = array{arr.l + (n - k + 1), k};
    nReplacemax(tree, &t);
    
    getNMaxValues(&arr, k);
  }
 return 0;
}
