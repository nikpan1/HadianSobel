// author: Nikodem Panknin
// title: Hadian-Sobel algorithm using tournament tree

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
void UpdatePath(vector<node> &tree, short int leaveID);
void BuildNode(vector<node> &tree, int nodeID);
int Replacemax(vector<node> &tree, int newMax);
void Visualize(vector<node> tree, array* leaves);
array NewRandomArray(short int n);


int main() {
    short int k = 5;  // k - ile największych elementów zwrócić
    short int n = 7;  // n - rozmiar tablicy
    
    array leaves = NewRandomArray(n);  // tworzenie losowej tablicy o rozmiarze n
    array temp = {leaves.l, short(n - k + 2)}; 
    vector<node> tree = Construct(&temp);
    
    Visualize(tree, &temp);
    cout << tree[0].mx << endl; 
    cout << Replacemax(tree, temp.l[n-k+3]) << endl;

    Visualize(tree, &temp);
    delete[] leaves.l;
    return 0;
}

inline vector<node> Construct(array* leaves) {
  const int h = treeHeight(leaves->size);   // wysokość drzewa
  const int tSize = treeSize(h) + 1;        // rozmiar drzewa 
  vector<node> tree(tSize, {0, 0});         // drzewo turniejowe, indexowane od 1
  tree[0] = {-1, -1};

  int n = firstLevelsId(h - 1), m = lastLevelsId(h - 1); // (n, m) - przedział h-1 warstwy 
  int nodesAmount = howMuchNodes(leaves->size, h);       // ilość węzłów w h-1 warstwie
  int pivot = 0;   // zamiast używać pivot, możemy dekrementować nodes amount
  
  // od n do n + nodes tworzymy węzły, które jako dzieci mają liście
  for (int i = n; i <= n + nodesAmount; i ++) {
    tree[L_ChildID(i)].mx = leaves->l[pivot ++];
    UpdatePath(tree, L_ChildID(i));
    tree[R_ChildID(i)].mx = leaves->l[pivot ++];    
    UpdatePath(tree, R_ChildID(i));
  }
  
  // w pozostałych (od n + nodes + 1 do m) przechowujemy liście
  for (int j = n + nodesAmount + 1; j <= m; j++) {
      tree[j].mx = leaves->l[pivot ++];
      UpdatePath(tree, j);
  }

  return tree;
}

void UpdatePath(vector<node> &tree, short int leaveID) {
  int pivot = leaveID;
  int LC  = 0, RC = 0;
  
  while (pivot > 1) {
    pivot = parentID(pivot);
    LC = L_ChildID(pivot);
    RC = R_ChildID(pivot);
    
    if (tree[tree[pivot].mx].mx > tree[leaveID].mx) {
      cout << "e - "<< tree[tree[pivot].mx].mx<<"_" << tree[leaveID].mx<<endl;
      tree[pivot].mn = leaveID;
      break;
    }
    else {
      tree[pivot].mn = tree[pivot].mx;
      tree[pivot].mx = leaveID;
    }
  }
}

int Replacemax(vector<node> &tree, int newMax) {
  int oldMax = tree[tree[1].mx].mx;
  int index = tree[1].mx;
  
  tree[tree[1].mx].mx = newMax;
  UpdatePath(tree, index);

  return oldMax;
}

void Visualize(vector<node> tree, array* leaves) {
  const int h = treeHeight(leaves->size);
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

array NewRandomArray(short int n) {
    srand(time(NULL));

    array leaves;
    leaves.size = n;
    leaves.l = new int[leaves.size];
    for (int i = 0; i < leaves.size; i++) leaves.l[i] = 10 + rand() % 1000;
    
    return leaves;
}
