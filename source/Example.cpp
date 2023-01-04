// author: Nikodem Panknin
// title: Hadian-Sobel algorithm example usage

#include <iostream>
#include <random>
#include "TournamentTree.hpp"
using namespace std;

void Visualize(vector<node> tree, array* leaves);
array NewRandomArray(short int n);


int main() {
  short int k = 3;  // k - ile największych elementów zwrócić
  short int n = 7;  // n - rozmiar tablicy
    
  array leaves = NewRandomArray(n);           // tworzenie losowej tablicy o rozmiarze n
  array temp = {leaves.l, short(n - k + 2)};  // wydzielenie tablicy o rozmiarze n - k + 2 
  vector<node> tree = Construct(&temp);
   
  Visualize(tree, &temp);
  Replacemax(tree, leaves.l[n - k + 2]); 
  Visualize(tree, &temp);

  delete[] leaves.l;
  return 0;
}

void Visualize(vector<node> tree, array* leaves) {
  const int h = treeHeight(leaves->size);

  cout << endl << "Tournament tree: " << endl;
  for (int j = 0; j <= h; j ++) {
    for (int i = firstLevelsId(j); i <= lastLevelsId(j); i ++) { 
      cout << i << "|" << tree[i].mx << ":" << tree[i].mn << "\t\t";
    }
    cout << endl;
  }  
}

array NewRandomArray(short int n) {
    srand(time(NULL));

    array leaves;
    leaves.size = n;
    leaves.l = new int[leaves.size];
    for (int i = 0; i < leaves.size; i++) leaves.l[i] = 10 + rand() % 1000;
    
    return leaves;
}
