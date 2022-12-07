#include <iostream>
#include <stdio.h>
#include <math.h>  // log
#include <cstdlib>  // rand
#include <cmath>  // ceil and pow
#include <random>

using namespace std;
// index 0, warstwa 0 to root
// indeksowanie jest zjebane jak wezme i = 1 --> mam 2 i 3, zamiast 3 i 4,
// musze indeksować drzewo o 1

// w sumie czy w liściach muszą być indeksy?

int treeSize(int tree_height) {
  return (int)pow(2, tree_height + 1) - 1;
}

int treeHeight(int leaves_size) {
  return (int)ceil(log2(leaves_size));
}

int firstLevelsId(int level) {
  return (int)pow(2, level);
}

int lastLevelsId(int level) {
  return firstLevelsId(level + 1) - 1;
}

int parentID(int child) {
  return (int)floor(child / 2);
}

int L_ChildID(int parentID) {
  return parentID * 2;
}

int R_ChildID(int parentID) {
  return L_ChildID(parentID) + 1;
}

int howMuchNodes(int leaves_amount, int height) {
  return leaves_amount - pow(2, height - 1);
}

void Visualize(int (*tree)[2], int size, int* leaves, int leaves_size) {
  cout << "Array: ";
  for(int j = 0; j < leaves_size; j++) cout << leaves[j] << ',';
  cout << endl << "Tournament tree: " << endl;

  for(int j = 0; j <= size; j ++) {
    for(int i = firstLevelsId(j); i <= lastLevelsId(j); i ++) { 
      cout << i << "|" << tree[i][0] << ":" << tree[i][1] << '\t';
    }
  cout << endl;
  }
}

void buildNode(int (*tree)[2], int* leaves, int nodeID) {
  if (leaves[tree[L_ChildID(nodeID)][0]] > leaves[tree[R_ChildID(nodeID)][0]]) {
    tree[nodeID][0] = L_ChildID(nodeID);
    tree[nodeID][1] = R_ChildID(nodeID);
  }
  else {
    tree[nodeID][0] = R_ChildID(nodeID);
    tree[nodeID][1] = L_ChildID(nodeID);
  }
}

void generateTreeFromArray(int* leaves, int leaves_size) {
  int height = treeHeight(leaves_size); 
  int size = treeSize(height);
  int tree[size + 1][2] = {0}; // indexujemy od 1
  int n = firstLevelsId(height - 1);
  int m = lastLevelsId(height - 1);
  int h = howMuchNodes(leaves_size - 1, height);
  int pivot = 0;

  cout << "height:" << height << endl << "size:" << size << endl;     // czy size się zgadza? 
  cout << "przedział p-1 warstwy: " << n << '-' << m << endl;
  cout << "Ile węzłów w p-1? - " << h << endl;

  for (int i = n; i <= n + h; i ++) {  // tutaj węzły
    tree[L_ChildID(i)][0] = pivot ++;
    tree[R_ChildID(i)][0] = pivot ++;    
    buildNode(tree, leaves, i);
    cout <<"a " << i << endl;
  }
  
  for (int j = n + h + 1; j <= m; j ++) {
    tree[j][0] = pivot ++;
    cout <<"b " << j << endl;
  }

  for (int i = n - 1; i > 0; i --) buildNode(tree, leaves, i);
  Visualize(tree, height, leaves, leaves_size);
}

void replacemax(int (*tree)[2]) {
  cout << " ";
}

int main() {
  srand( time(NULL) );
  int leaves_size = 4 + rand() % 10;
  int leaves [leaves_size];
  cout << "leaves_size = " << leaves_size << endl;
  for(int i = 0; i < leaves_size; i ++) leaves[i] = 1 + rand() % 100;
  
  generateTreeFromArray(leaves, leaves_size);
  return 0;
}


