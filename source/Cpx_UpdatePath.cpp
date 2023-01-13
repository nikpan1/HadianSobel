#include <iostream>
#include "TournamentTree.hpp"
using namespace std;

int main() {

  int counter = 0;
  for (int i = 0; i < 10000; i ++) {
    for (int k = 0; k < 50; k ++ ) {
      array arr = NewRandomArray(i);
      HadianSobel(&arr, int(i/2), counter);
      delete[] arr.l;
    }
    cout  << i << "\t" << double(double(counter) / 50) << endl;
    counter = 0;
  }  

  return 0;
}
