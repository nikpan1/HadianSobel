// author: Nikodem Panknin
// title: Hadian-Sobel algorithm example usage

#include <iostream>
#include "Array.hpp"
#include "TournamentTree.hpp"
using namespace std;


int main() {
  short int k = 1;  // k - ile największych elementów zwrócić
  short int n = 10;  // n - rozmiar tablicy

  array leaves = NewRandomArray(n);           // tworzenie losowej tablicy o rozmiarze n
  array temp = {leaves.l, short(n - k + 1)};  // wydzielenie tablicy o rozmiarze n - k + 1 (tablice numeruję od 0) 
  vector<node> tree = Construct(&temp);
  
  cout << "n = " << n <<", k = " << k << endl;
  printArray(&leaves);
  Visualize(tree, &temp);

/*
  auto t = array{leaves.l + (n - k + 1), k};
  nReplacemax(tree, &t);
  Visualize(tree, &temp);
*/

  delete[] leaves.l;
  return 0;
}
