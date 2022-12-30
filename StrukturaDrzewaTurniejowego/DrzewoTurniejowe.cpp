#include <iostream>
#include <math.h>  // log
#include <cmath>  // ceil and pow
#include <random>

using namespace std;

#define treeHeight(l) int(ceil(log2(l)))             // wysokość drzewa = sufit(log2(l)), gdzie l - ilość liści
#define treeSize(h) int(pow(2, h + 1) - 1)           // rozmiar drzewa = 2^(h+1) + 1, gdzie h - wysokość drzewa
#define firstLevelsId(n) int(pow(2, n))              // pierwszy indeks n-tej warstwy = 2^n
#define lastLevelsId(n) int(pow(2, n + 1) - 1)       // ostatni indeks n-tej warstwy = 2^(n+1) - 1
#define parentID(childID) int(floor(childID / 2))    // indeks rodzica = entier(childID / 2), gdzie childID to indeks dziecka
#define L_ChildID(parentID) int(parentID * 2)        // lewe dziecko = 2 * parentId, gdzie parentID to indeks rodzica  
#define R_ChildID(parentID) int(2 * parentID + 1)    // prawe dziecko = 2 * parentID + 1, gdzie parentID to indeks rodzica
#define howMuchNodes(l, h) int(l - pow(2, h - 1))    // ilość węzłów w drzewie = l - 2^(h-1), gdzie l - ilość liści, h - wysokość drzewa 

void Visualize(int (*tree)[2], int treeSize, int* leaves, int leavesSize);
void BuildNode(int (*tree)[2], int nodeID);
void GenerateTreeFromArray(int* leaves, int leavesSize);
void Replacemax(int (*tree)[2], int newMax);

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

void GenerateTreeFromArray(int* leaves, int leavesSize) {
  int height = treeHeight(leavesSize); 
  int size = treeSize(height);
  int tree[size + 1][2] = {0}; // indexujemy od 1
  int n = firstLevelsId(height - 1);
  int m = lastLevelsId(height - 1);
  int h = howMuchNodes(leavesSize - 1, height);
  int pivot = 0;

  cout << "height:" << height << endl << "size:" << size << endl;      
  cout << "przedział p-1 warstwy: " << n << '-' << m << endl;
  cout << "Ile węzłów w p-1? - " << h << endl;

  for (int i = n; i <= n + h; i ++) {  // tutaj węzły
    tree[L_ChildID(i)][0] = leaves[pivot ++];
    tree[R_ChildID(i)][0] = leaves[pivot ++];    
    BuildNode(tree, i);
  }
  
  for (int j = n + h + 1; j <= m; j ++) tree[j][0] = leaves[pivot ++];
  for (int i = n - 1; i > 0; i --) BuildNode(tree, i);
  Visualize(tree, height, leaves, leavesSize);
}

void Replacemax(int (*tree)[2], int newMax) {
  cout << " ";
}

int main() {
  srand( time(NULL) );
  int leaves_size = 4 + rand() % 10;
  int leaves [leaves_size];
  cout << "leaves_size = " << leaves_size << endl;
  for(int i = 0; i < leaves_size; i ++) leaves[i] = 100 + rand() % 100;
  
  GenerateTreeFromArray(leaves, leaves_size);
  return 0;
}

void Visualize(int (*tree)[2], int treeSize, int* leaves, int leavesSize) {
  cout << "Array: ";
  for (int j = 0; j < leavesSize; j++) cout << leaves[j] << ' ';

  cout << endl << "Tournament tree: " << endl;
  for (int j = 0; j <= treeSize; j ++) {
    for (int i = firstLevelsId(j); i <= lastLevelsId(j); i ++) { 
      cout << i << "|" << tree[i][0] << ":" << tree[i][1] << '\t';
    }
    cout << endl;
  }
}

