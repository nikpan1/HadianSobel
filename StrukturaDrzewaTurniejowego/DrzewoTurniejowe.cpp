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

void Visualize(int (*tree)[2], int size) {
  for(int j = 0; j <= size; j ++) {
    for(int i = firstLevelsId(j); i <= lastLevelsId(j); i ++) { 
      cout << i << "|" << tree[i][0] << ":" << tree[i][1] << "    ";
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

void generateTreeFromArray(int* leaves, int l, int r) {
  int height = treeHeight(r + 1); 
  int size = treeSize(height);

  cout << "l:" << l << endl << "r:" << r <<endl;
  cout << "height:" << height << endl << "size:" << size << endl; 
  cout << "pierwszy element p - 1 warstwy: " << firstLevelsId(height - 1) << endl;
  cout << "iteracja aż do: " << lastLevelsId(height - 1) << endl;
  cout << "ile z nich to węzły: " << howMuchNodes(r + 1, height) << endl;

  int tree[size + 1][2]; // inicjalizujemy od 1
  for (int i = 0; i < size + 1; i ++) {
    tree[i][0] = -1;
    tree[i][1] = -1;
  }
  int n = firstLevelsId(height - 1);
  int m = lastLevelsId(height - 1);
  int pivot {};
  
  for (int i = n; i < n + howMuchNodes(r, height); i ++) {
    // tutaj węzły
    tree[L_ChildID(i)][0] = leaves[pivot];
    pivot ++;
    tree[R_ChildID(i)][0] = leaves[pivot];
    pivot ++;
    
    buildNode(tree, leaves, i);

    cout <<"a " << i << endl;
  }
  
  for (int j = n + howMuchNodes(r, height); j < m + 1; j ++) {
    tree[j][0] = leaves[pivot];
    pivot ++;
    cout <<"b " << j << endl;
  }

  for (int i = n - 1; i > 1; i --) buildNode(tree, leaves, i);
  Visualize(tree, height);
}

int main() {
  srand( time(NULL) );
  int leaves_size = 4 + rand() % 10;
  int leaves [leaves_size];
  cout << "size0 = " << leaves_size << endl;
  for(int i = 0; i < leaves_size; i ++) leaves[i] = 1 + rand() % 100;
  
  generateTreeFromArray(leaves, 0, leaves_size - 1);
  
  return 0;
}


