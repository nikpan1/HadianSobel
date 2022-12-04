#include <iostream>
#include <stdio.h>
#include <math.h>  // log
#include <cstdlib>  // rand
#include <cmath>  // ceil and pow
#include <random>

using namespace std;

  
bool goLeft() {
  return rand() % 2; 
}
void printTree(int (*tree)[2], int tree_height) {
  int index {1};
  for (int i = 0; i < tree_height; i ++) {
    for (int j = 0; j < pow(2, i); j ++) {
    cout << "|" << tree[index][0] << "_" << tree[index][1] << "|" << " ";
      index ++;
    }
    cout << endl;
  }
}

int generateNode(int (*tree)[2], int tree_height, int index) {
  if (tree_height < 2) {
//    cout << "end" << endl;
    return 0;
  }
  bool gl = goLeft();
  tree[2 * index][0] = tree[index][gl];
  tree[2 * index + 1][0] = tree[index][!gl];
  tree[2 * index][1] = rand() % tree[index][0];
  tree[2 * index + 1][1] = rand() % tree[index][1];
  generateNode(tree, tree_height - 1, 2 * index);
  generateNode(tree, tree_height - 1, 2 * index + 1);
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
  for (int i = 0; i < tree_size + 1; i ++) {
    tree[i][0] = -1;
    tree[i][1] = -1;
  }
  
  tree[1][0] = 1000;
  tree[1][1] = 994;

  // Uwaga - węzły powinny przechowywać tylko indeksy liści

  generateNode(tree, tree_height, 1);
  printTree(tree, tree_height);


  cout << "leaves_amount = " << leaves_amount << endl;
  cout << "tree_height = " << tree_height << endl;
  cout << "tree_size = " << tree_size << endl;
  return 0;
}
