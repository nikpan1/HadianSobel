// author: Nikodem Panknin
// title: Hadian-Sobel algorithm example usage

#include <iostream>
#include "Array.hpp"
#include "TournamentTree.hpp"
using namespace std;


int main() {
  short int k = 7;  // k - ile największych elementów zwrócić
  short int n = 10;  // n - rozmiar tablicy
  double x = 0;

  array leaves = NewRandomArray(n);           // tworzenie losowej tablicy o rozmiarze n
  array temp = {leaves.l, short(n - k + 1)};  // wydzielenie tablicy o rozmiarze n - k + 1 (tablice numeruję od 0) 
  vector<node> tree = Construct(&temp, x);
  
  cout << "n = " << n <<", k = " << k << endl;
  printArray(&leaves);
  Visualize(tree, &temp);


  Replacemax(tree, 100);
  Visualize(tree, &temp);


  delete[] leaves.l;
  return 0;
}
