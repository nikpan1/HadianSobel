#include <iostream>
#include <vector>

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

struct node { int mx; int mn; };
struct array { int* l; short int size; };

vector<node> Construct(array* leaves);
void BuildNode(vector<node> &tree, int nodeID);
void Replacemax(vector<node> &tree, int newMax);
void Visualize(vector<node> tree, array* leaves, int h);


inline vector<node> Construct(array* leaves) {
  const int h = treeHeight(leaves->size);   // wysokość drzewa
  const int tSize = treeSize(h) + 1;        // liczba pamięci potrzebnej do zaalokowania pamięci 
  vector<node> tree(tSize, {0, 0});         // drzewo turniejowe, indexowane od 1
  int n = firstLevelsId(h - 1);             // (n, m) to przedział przedostatniej warstwy 
  int m = lastLevelsId(h - 1);

  int nodesAmount = howMuchNodes(leaves->size, h);    // ilość węzłów w przedostatniej warstwy
  int pivot = 0;

  // od n do n + nodes tworzymy węzły, które jako dzieci mają liście
  for (int i = n; i <= n + nodesAmount; i ++) { 
    tree[L_ChildID(i)].mx = leaves->l[pivot ++];
    tree[R_ChildID(i)].mx = leaves->l[pivot ++];    
    BuildNode(tree, i);
  }
  
  // w pozostałych (od n + nodes + 1 do m) przechowujemy liście
  for (int j = n + nodesAmount + 1; j <= m; j ++) tree[j].mx = leaves->l[pivot ++];  
  // następnie iterujemy od n - 1 do 1 budując kolejne węzły
  for (int i = n - 1; i > 0; i --) BuildNode(tree, i);

  Visualize(tree, leaves, h);
  return tree;
}

void BuildNode(vector<node> &tree, int nodeID) {
  int LC = L_ChildID(nodeID);
  int RC = R_ChildID(nodeID);
  
  bool LC_isNode = (tree[LC].mn != 0);
  bool RC_isNode = (tree[RC].mn != 0);
    
  int LC_CMP = !LC_isNode ? tree[LC].mx : tree[tree[LC].mx].mx;
  int RC_CMP = !RC_isNode ? tree[RC].mx : tree[tree[RC].mx].mx;

  if (LC_CMP > RC_CMP) {
    tree[nodeID].mx = LC_isNode ? tree[LC].mx : LC;
    tree[nodeID].mn = RC_isNode ? tree[RC].mx : RC;
  }
  else {
    tree[nodeID].mx = RC_isNode ? tree[RC].mx : RC;
    tree[nodeID].mn = LC_isNode ? tree[LC].mx : LC;
  }
}

void Replacemax(vector<node> &tree, int newMax) {
  cout << "Replacemax";
}


int main() {
  srand( time(NULL) );

  array leaves;
  leaves.size = 4 + rand() % 10;
  leaves.l = new int [leaves.size];
  for(int i = 0; i < leaves.size; i ++) leaves.l[i] = 100 + rand() % 100; 

  vector<node> tree = Construct(&leaves);
  
  delete [] leaves.l;
  return 0;
}

void Visualize(vector<node> tree, array* leaves, int h) {
  cout << "Array: ";
  for (int j = 0; j < leaves->size; j++) cout << leaves->l[j] << ' ';

  cout << endl << "Tournament tree: " << endl;
  for (int j = 0; j <= h; j ++) {
    for (int i = firstLevelsId(j); i <= lastLevelsId(j); i ++) { 
      cout << i << "|" << tree[i].mx << ":" << tree[i].mn << "\t\t";
    }
    cout << endl;
  }
}

