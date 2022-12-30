#include <iostream>
#include <stdio.h>
#include <math.h>  // log
#include <cstdlib>  // rand
#include <cmath>  // ceil and pow
#include <random>
#include <string>

using namespace std;

#define treeHeight(leaves_size) int(ceil(log2(leaves_size)))      // wysokość drzewa = sufit(log2(l)), gdzie l - ilość liści
#define treeSize(tree_height) int(pow(2, tree_height + 1) - 1)    // rozmiar drzewa = 2^(h+1) + 1, gdzie h - wysokość drzewa
#define firstLevelsId(n) int(pow(2, n))                           // pierwszy indeks n-tej warstwy = 2^n
#define lastLevelsId(n) int(pow(2, n + 1) - 1)                    // ostatni indeks n-tej warstwy = 2^(n+1) - 1
#define parentID(childID) int(floor(childID / 2))                 // indeks rodzica = entier(childID / 2), gdzie childID to indeks dziecka
#define L_ChildID(parentID) int(parentID * 2)                     // lewe dziecko = 2 * parentId, gdzie parentID to indeks rodzica  
#define R_ChildID(parentID) int(2 * parentID + 1)                 // prawe dziecko = 2 * parentID + 1, gdzie parentID to indeks rodzica
#define howMuchNodes(leaves_amount, height) int(leaves_amount - pow(2, height - 1))

//void Visualize
//void buildNode
//void generateTreeFromArray
//void replacemax

void Visualize(int (*tree)[2], int size, int* leaves, int leaves_size) {
  cout << "Array: ";
  for (int j = 0; j < leaves_size; j++) cout << leaves[j] << ',';
  cout << endl << "Tournament tree: " << endl;
  
  for (int j = 0; j <= size; j ++) {
    for (int i = firstLevelsId(j); i <= lastLevelsId(j); i ++) { 
      cout << i << "|" << tree[i][0] << ":" << tree[i][1] << '\t';
    }
    cout << endl;
  }
}

void buildNode(int (*tree)[2], int nodeID) {
  int LC = L_ChildID(nodeID);
  int RC = R_ChildID(nodeID);
  
  bool LC_isNode = (tree[LC][1] != 0);
  bool RC_isNode = (tree[RC][1] != 0);
    
  int LC_CMP = !LC_isNode ? tree[LC][0] : tree[tree[LC][0]][0];
  int RC_CMP = !RC_isNode ? tree[RC][0] : tree[tree[RC][0]][0];

  if (LC_CMP > RC_CMP) {
    tree[nodeID][0] = LC_isNode ? tree[LC][0] : LC;
    tree[nodeID][1] = RC_isNode ? tree[RC][0] : RC;
  }
  else {
    tree[nodeID][0] = RC_isNode ? tree[RC][0] : RC;
    tree[nodeID][1] = LC_isNode ? tree[LC][0] : LC;
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
    tree[L_ChildID(i)][0] = leaves[pivot ++];
    tree[R_ChildID(i)][0] = leaves[pivot ++];    
    buildNode(tree, i);
    cout <<"a " << i << endl;
  }
  
  for (int j = n + h + 1; j <= m; j ++) {
    tree[j][0] = leaves[pivot ++];
    cout <<"b " << j << endl;
  }

  for (int i = n - 1; i > 0; i --) buildNode(tree, i);
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
  for(int i = 0; i < leaves_size; i ++) leaves[i] = 100 + rand() % 100;
  
  generateTreeFromArray(leaves, leaves_size);
  return 0;
}


