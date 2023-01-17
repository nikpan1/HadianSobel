// author: Nikodem Panknin
// title: Hadian-Sobel algorithm using tournament tree

#pragma once
#include <vector>
#include <cmath>
#include "Array.hpp"
using namespace std;


#define SEPARATOR " "

#define treeHeight(l) int(ceil(log2(l)))              // wysokość drzewa - sufit(log2(l)), gdzie l - ilość liści
#define treeSize(l) int(3 * l)                        // rozmiar drzewa - 2 * l, gdzie l to ilość liści
#define parentID(childID) int(floor(childID / 2))     // indeks rodzica - entier(childID / 2), gdzie childID to indeks dziecka
#define L_ChildID(parentID) int(parentID * 2)         // indeks lewego dziecka - 2 * parentID, gdzie parentID to indeks rodzica  
#define R_ChildID(parentID) int(2 * parentID + 1)     // indeks prawego dziecka - 2 * parentID + 1, gdzie parentID to indeks rodzica
#define leaveID(i) int((2.0/3.0) * tree.size() + i)   // indeks liścia na podstawie indeksu połączenia
#define twigID(i) int(i - (1.0/3.0) * tree.size())    // indeks połączenia drzewa na podstawie indeksu liścia
#define val(i) tree[tree[i].mx].mx                    // val() - wartość przechowywana przez liść o indeksie i

struct node { int mx; int mn; };     // struktura węzłów drzewa

vector<node> Construct(array* leaves, double& counter); // funkcja budująca strukturę drzewa turniejowego
void UpdatePath(vector<node>& tree, int pivot);         // funkcja aktualizująca drzewo przechodząc od liścia wskazywanego przez pivot, aż do korzenia 
void Replacemax(vector<node>& tree, int newVal);        // funkcja wstawiająca nową wartość na miejsce starego maximum drzewa turniejowego
void HadianSobel(array* list, int k);                   // funkcja wykonująca algorytm hadiana-Sobela wyznaczając k największych wartości


void UpdatePath(vector<node>& tree, int pivot) {
  // jeżeli lewe dziecko trzyma w mx większą wartość niż prawe dziecko w mx
  if ( val(L_ChildID(pivot)) > val(R_ChildID(pivot)) ) {
    // to niech węzeł wskazywany przez pivot przyjmie wartości 
    tree[pivot].mx = tree[L_ChildID(pivot)].mx;
    tree[pivot].mn = tree[R_ChildID(pivot)].mx;
  }
  else {
    // w przeciwnym wypadku
    tree[pivot].mn = tree[L_ChildID(pivot)].mx;
    tree[pivot].mx = tree[R_ChildID(pivot)].mx;
  }
}

vector<node> Construct(array* leaves) {
  // n - rozmiar tablicy wejściowej
  int n = leaves->size;
  // alokacja pamięci na potrzeby struktury
  // indeksowanie od 1, wyzerowane wartości początkowe
  vector<node> tree(treeSize(n), {0, 0});
  
  // od 0 do n
  for (int i = 0; i < n; i ++) {  
    // wpisuje kolejne elementy jako liście drzewa
    tree[n + i].mx = leaveID(i);
    tree[leaveID(i)].mx = leaves->l[i];
  }
 
  // od n - 1 do korzenia 
  // kolejne aktualizowanie wartości węzła 
  for (int i = n - 1; i >= 1; i --) UpdatePath(tree, i);
  
  return tree;
}

void Replacemax(vector<node>& tree, int newVal) {
  // nowa wartość na pozycji starego maximum drzewa
  val(1) = newVal; 
 
  // schodzenie od liścia, gdzie znajduje się nowa wartość, aż do korzenia
  int pivot = twigID(tree[1].mx);
  while (pivot > 1) {
    pivot = parentID(pivot);
    // aktualizuje przy każdej iteracji węzeł wskazywany przez pivot
    UpdatePath(tree, pivot);
  }
}

void HadianSobel(array* list, int k) {
  // rozmiar listy wejściowej
  int n = list->size; 
  // wydzielenie tablicy o rozmiarze n - k + 1
  array leaves = {list->l, short(n - k + 1)};
  // tworzenie drzewa
  vector<node> tree = Construct(&leaves);
  
  // czytanie oraz wywołanie Replacemax n-k+1 razy 
  for (int i = n - k + 1; i < n; i ++) {
    cout << val(1) << SEPARATOR;
    Replacemax(tree, leaves.l[n-k + i]);
  }

  cout << val(1) << endl;
}

// _______________________

void Visualize(vector<node> tree, array* leaves);

void Visualize(vector<node> tree, array* leaves) {
  cout << endl << "Tournament tree: " << endl;
  for (int j = 0; j <= treeHeight(leaves->size); j++) {
    for (int i = pow(2, j); i < pow(2, j + 1); i++) {
      cout << i << "|" << tree[i].mx << ":" << tree[i].mn << "\t\t";
    }
    cout << endl;
  }
  cout << endl;
  for(int i = 0; i < leaves->size; i++)
    cout << tree.size() - 1 -i <<"_"<<tree[tree.size() - 1 - i].mx << ",";
  cout << endl;
}

