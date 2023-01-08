#include <iostream>
#include "Array.hpp"
#include "TournamentTree.hpp"
using namespace std;

#define SEPARATOR "\t"

int main() {
  int mx = 49;
  double counter = 0;
  array leaves;

  for (int x = 2; x < 1000; x++) {
    for (int i = 0; i < mx; i ++) {
      leaves = NewRandomArray(x);
      Construct(&leaves, counter);
      delete[] leaves.l;
    }
    cout << x << SEPARATOR << counter/mx << endl;
    counter = 0;
  }


}
