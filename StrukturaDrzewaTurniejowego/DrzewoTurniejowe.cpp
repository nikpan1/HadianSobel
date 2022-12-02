#include <iostream>
#include <stdio.h>
#include <math.h>  // log
#include <cstdlib>  // rand
#include <cmath>  // ceil and pow

using namespace std;

int generateNode(int *tree, int tree_size, int tree_height, int index) {
  // tu wszystko się zachowuje rekurencyjnie
  // ważna uwaga
  // dwie ostatnie warstwy się inaczej zachowują
  // --> mogą być już liście w przedostaniej warstwie
  // --> każdy węzeł musi mieć 2 dzieci
  return 0;
}

int main() {
  srand( time(NULL) );
  int leaves_amount = rand() % 30;
  int tree_height = ceil(log2(leaves_amount));
  
  int tree_size {0};
  for (int i = 0; i < tree_height; i ++) tree_size += pow(2, i);
  
  int tree[tree_size + 1][2]; // index 0 - wartownik, drzewo od 1
  // mx - [i][0] - max(mx(2i), mx(2i + 1))
  // mn - [i][1] - min(mx(2i), mx(2i + 1))
  // Uwaga - węzły powinny przechowywać tylko indeksy liści

  tree[0][1] = -1;
  tree[0][0] = -1;


  cout << "leaves_amount = " << leaves_amount << endl;
  cout << "tree_height = " << tree_height << endl;
  cout << "tree_size = " << tree_size << endl;
  return 0;
}
