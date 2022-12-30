#include <iostream>
#include <math.h>    // log2
#include <cmath>     // ceil, pow
#include <random>    // rand

using namespace std;


#define treeHeight(l) int(ceil(log2(l)))              // wysokość drzewa = sufit(log2(l)), gdzie l - ilość liści
#define treeSize(h) int(pow(2, h + 1) - 1)            // rozmiar drzewa = 2^(h+1) + 1, gdzie h - wysokość drzewa
#define firstLevelsId(n) int(pow(2, n))               // pierwszy indeks n-tej warstwy = 2^n
#define lastLevelsId(n) int(pow(2, n + 1) - 1)        // ostatni indeks n-tej warstwy = 2^(n+1) - 1
#define parentID(childID) int(floor(childID / 2))     // indeks rodzica = entier(childID / 2), gdzie childID to indeks dziecka
#define L_ChildID(parentID) int(parentID * 2)         // lewe dziecko = 2 * parentId, gdzie parentID to indeks rodzica  
#define R_ChildID(parentID) int(2 * parentID + 1)     // prawe dziecko = 2 * parentID + 1, gdzie parentID to indeks rodzica
#define howMuchNodes(l, h) int(l - 1 - pow(2, h - 1)) // ilość węzłów w drzewie = l - 2^(h-1), gdzie l - ilość liści, h - wysokość drzewa 

void GenerateTreeFromArray(int* leaves, int leavesSize);
void BuildNode(int (*tree)[2], int nodeID);
void Replacemax(int (*tree)[2], int newMax);
void Visualize(int (*tree)[2], int treeSize, int* leaves, int leavesSize);

void BuildNode(int (*tree)[2], int nodeID) {
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

inline void GenerateTreeFromArray(int* leaves, int leavesSize) {
  int h = treeHeight(leavesSize);   // wysokość drzewa
  int mem = treeSize(h) + 1;        // liczba pamięci potrzebnej do zaalokowania pamięci 
  int tree[mem][2] = {0};           // drzewo turniejowe, w postaci dwuwymiarowej tablicy 2 x AM, indexowane od 1
                                    // (n, m) to przedział przedostatniej warstwy 
  
  int n = firstLevelsId(h - 1), m = lastLevelsId(h - 1);
  int nodes = howMuchNodes(leavesSize, h);    // ilość węzłów w przedostatniej warstwy
  int pivot = 0;

  // od n do n + nodes tworzymy węzły, które jako dzieci mają liście
  for (int i = n; i <= n + nodes; i ++) { 
    tree[L_ChildID(i)][0] = leaves[pivot ++];
    tree[R_ChildID(i)][0] = leaves[pivot ++];    
    BuildNode(tree, i);
  }
  
  // w pozostałych (od n + nodes + 1 do m) przechowujemy liście
  for (int j = n + nodes + 1; j <= m; j ++) tree[j][0] = leaves[pivot ++];  
  // następnie iterujemy od n - 1 do 1 budując kolejne węzły
  for (int i = n - 1; i > 0; i --) BuildNode(tree, i);

  Visualize(tree, h, leaves, leavesSize);
}

void Replacemax(int (*tree)[2], int newMax) {
  int pivot = tree[1][1];
  tree[pivot][0] = newMax;
  
  while (pivot >= 1) {
    
    pivot = parentID(pivot);
  }
}


int main() {
  srand( time(NULL) );
  int leavesSize = 4 + rand() % 10;
  int leaves [leavesSize];

  for(int i = 0; i < leavesSize; i ++) leaves[i] = 100 + rand() % 100; 
  GenerateTreeFromArray(leaves, leavesSize);
  return 0;
}

void Visualize(int (*tree)[2], int treeSize, int* leaves, int leavesSize) {
  cout << "Array: ";
  for (int j = 0; j < leavesSize; j++) cout << leaves[j] << ' ';

  cout << endl << "Tournament tree: " << endl;
  for (int j = 0; j <= treeSize; j ++) {
    for (int i = firstLevelsId(j); i <= lastLevelsId(j); i ++) { 
      cout << i << "|" << tree[i][0] << ":" << tree[i][1] << "\t\t";
    }
    cout << endl;
  }
}

