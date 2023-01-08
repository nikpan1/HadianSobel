// author: Nikodem Panknin
// title: Hadian-Sobel algorithm using tournament tree

#pragma once
#include <vector>
#include <cmath>
#include "Array.hpp"
using namespace std;


#define treeHeight(l) int(ceil(log2(l)))              // wysokosc drzewa = sufit(log2(l)), gdzie l - ilosc lisci
#define treeSize(l) int(3 * l)                        // rozmiar drzewa = 2*l, gdzie l - ilosc lisci
#define parentID(childID) int(floor(childID / 2))     // indeks rodzica = entier(childID / 2), gdzie childID to indeks dziecka
#define L_ChildID(parentID) int(parentID * 2)         // lewe dziecko = 2 * parentID, gdzie parentID to indeks rodzica  
#define R_ChildID(parentID) int(2 * parentID + 1)     // prawe dziecko = 2 * parentID + 1, gdzie parentID to indeks rodzica
#define l_Id(i) int((2.0/3.0)*tree.size() + i)
#define twig_Id(i) int(i - (1.0/3.0)*tree.size())
#define val(i) tree[tree[i].mx].mx

struct node { int mx; int mn; };            // struktura wezlow drzewa

vector<node> Construct(array* leaves, double& counter);
void UpdatePath(vector<node>& tree, int pivot);
void Replacemax(vector<node>& tree, int newMax, double& counter);        // Replacemax dla jednego liscia
void nReplacemax(vector<node>& tree, array* n);
void Visualize(vector<node> tree, array* leaves);


void UpdatePath(vector<node>& tree, int pivot) {
  if ( val(L_ChildID(pivot)) > val(R_ChildID(pivot)) ) {
    tree[pivot].mx = tree[L_ChildID(pivot)].mx;
    tree[pivot].mn = tree[R_ChildID(pivot)].mx;
  }
  else {
    tree[pivot].mn = tree[L_ChildID(pivot)].mx;
    tree[pivot].mx = tree[R_ChildID(pivot)].mx;
  }
}


inline vector<node> Construct(array* leaves) {
  vector<node> tree(treeSize(leaves->size), {0, 0}); // drzewo turniejowe, indexowane od 1
  
  for (int i = 0; i < leaves->size; i ++) {
    tree[leaves->size + i].mx = l_Id(i);
    tree[l_Id(i)].mx = leaves->l[i];
  }

  for (int i = leaves->size - 1; i >= 1; i --) UpdatePath(tree, i);
  return tree;
}

void Replacemax(vector<node>& tree, int newMax) {
  val(1) = newMax;

  int pivot = twig_Id(tree[1].mx);
  while (pivot > 1) {
    pivot = parentID(pivot);
    UpdatePath(tree, pivot);
  }
}

void nReplacemax(vector<node>& tree, array* n) {
  for (int i = 0; i < n->size; i++) Replacemax(tree, n->l[i]);
  cout << endl;
}

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

