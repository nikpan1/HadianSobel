// author: Nikodem Panknin
// title: Hadian-Sobel algorithm using tournament tree

#include <iostream>
#include <vector>
#include <math.h>    // log2
#include <cmath>     // ceil, floor, pow
#include <random>    // rand

using namespace std;


#define treeHeight(l) int(ceil(log2(l)))              // wysokość drzewa = sufit(log2(l)), gdzie l - ilość liści
#define treeSize(h) int(pow(2, h + 1))                // rozmiar drzewa = 2^(h+1) - 1 + 1, gdzie h - wysokość drzewa
#define firstLevelsId(n) int(pow(2, n))               // pierwszy indeks n-tej warstwy = 2^n
#define lastLevelsId(n) int(pow(2, n + 1) - 1)        // ostatni indeks n-tej warstwy = 2^(n+1) - 1
#define parentID(childID) int(floor(childID / 2))     // indeks rodzica = entier(childID / 2), gdzie childID to indeks dziecka
#define L_ChildID(parentID) int(parentID * 2)         // lewe dziecko = 2 * parentID, gdzie parentID to indeks rodzica  
#define R_ChildID(parentID) int(2 * parentID + 1)     // prawe dziecko = 2 * parentID + 1, gdzie parentID to indeks rodzica
#define howMuchNodes(l, h) int(l - 1 - pow(2, h - 1)) // ilość węzłów w drzewie = l - 2^(h-1), gdzie l - ilość liści, h - wysokość drzewa 
// #define OppositeChild(l) (l % 2 == 0) ? int(l + 1) : int(l - 1) 

struct node { int mx; int mn; };
struct array { int* l; short int size; };

vector<node> Construct(array* leaves);
void UpdatePath(vector<node> &tree, short int leaveID, int val);
void Replacemax(vector<node> &tree, int newMax);
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

inline vector<node> Construct(array* leaves) {
  const int h = treeHeight(leaves->size);  // wysokość drzewa
  vector<node> tree(treeSize(h), {0, 0});  // drzewo turniejowe, indexowane od 1
  tree[0] = {-1, -1};                      // wartownik ustawiony w tree[0]

  int n = firstLevelsId(h - 1), m = lastLevelsId(h - 1); // (n, m) - przedział h-1 warstwy 
  int nodesAmount = howMuchNodes(leaves->size, h);       // ilość węzłów w h-1 warstwie
  int pivot = 0;

  for (int i = n; i <= n + nodesAmount; i ++) {     // tworzymy liście, gdzie w n-1 tworzą węzły
    UpdatePath(tree, L_ChildID(i), leaves->l[pivot ++]);
    UpdatePath(tree, R_ChildID(i), leaves->l[pivot ++]);
  }
  for (int j = n + nodesAmount + 1; j <= m; j++) {  // tworzymy liście będące w n-1 
    UpdatePath(tree, j, leaves->l[pivot ++]);
  }

  return tree;
}

void UpdatePath(vector<node> &tree, short int leaveID, int val) {
  short int pivot = leaveID; 
  tree[leaveID].mx = val;   // ustawiam val liścia

  while (pivot > 1) {   // schodzenie do rodzica, aż do korzenia
    pivot = parentID(pivot);    
    if (tree[tree[pivot].mx].mx > tree[leaveID].mx) {   
      tree[pivot].mn = leaveID;
      leaveID = tree[pivot].mx; 
      break;
    }
    else { 
      tree[pivot].mn = tree[pivot].mx;
      tree[pivot].mx = leaveID;
    }
  }
}

void Replacemax(vector<node> &tree, int newMax) {
  short int pivot = tree[1].mx;
  short int leaveID = tree[1].mx;
  tree[leaveID].mx = newMax;    // ustawia nową wartość val, zamiast max

  while (pivot > 1) {    // schodzenie do rodzica, aż do korzenia
    pivot = parentID(pivot);
    if (newMax < tree[tree[pivot].mn].mx){
      tree[pivot].mx = tree[pivot].mn;
      tree[pivot].mn = leaveID;
      leaveID = tree[pivot].mx;
    }
    else tree[pivot].mx = leaveID;  // ? 
  }
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

