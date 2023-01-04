// author: Nikodem Panknin
// title: Hadian-Sobel algorithm using tournament tree

#pragma once
#include <vector>
#include <cmath>
#include "Array.hpp"
using namespace std;


#define treeHeight(l) int(ceil(log2(l)))              // wysoko¿¿ drzewa = sufit(log2(l)), gdzie l - iloœæ liœci
#define treeSize(h) int(pow(2, h + 1))                // rozmiar drzewa = 2^(h+1) - 1 + 1, gdzie h - wysokoœæ drzewa
#define firstLevelsId(n) int(pow(2, n))               // pierwszy indeks n-tej warstwy = 2^n
#define lastLevelsId(n) int(pow(2, n + 1) - 1)        // ostatni indeks n-tej warstwy = 2^(n+1) - 1
#define parentID(childID) int(floor(childID / 2))     // indeks rodzica = entier(childID / 2), gdzie childID to indeks dziecka
#define L_ChildID(parentID) int(parentID * 2)         // lewe dziecko = 2 * parentID, gdzie parentID to indeks rodzica  
#define R_ChildID(parentID) int(2 * parentID + 1)     // prawe dziecko = 2 * parentID + 1, gdzie parentID to indeks rodzica
#define howMuchNodes(l, h) int(l - 1 - pow(2, h - 1)) // iloœæ wêz³ów w drzewie = l - 2^(h-1), gdzie l - iloœæ liœci, h - wysokoœæ drzewa  

struct node { int mx; int mn; };            // struktura wêz³ów drzewa

vector<node> Construct(array* leaves);
void UpdatePath(vector<node>& tree, short int leaveID, int val);
void Replacemax(vector<node>& tree, int newMax);        // Replacemax dla jednego liœcia
void nReplacemax(vector<node>& tree, array* n);
void Visualize(vector<node> tree, array* leaves);

inline vector<node> Construct(array* leaves) {
    const int h = treeHeight(leaves->size);   // wysokoœæ drzewa
    vector<node> tree(treeSize(h), { 0, 0 }); // drzewo turniejowe, indexowane od 1
    tree[0] = { -1, -1 };                     // wartownik ustawiony w tree[0]

    int n = firstLevelsId(h - 1), m = lastLevelsId(h - 1); // (n, m) - przedzia³ h-1 warstwy 
    int nodesAmount = howMuchNodes(leaves->size, h);       // iloœæ wêz³ów w h-1 warstwie
    int pivot = 0;

    for (int i = n; i <= n + nodesAmount; i++) {      // tworzymy liœcie, gdzie w n-1 tworz¹ wêz³y
        UpdatePath(tree, L_ChildID(i), leaves->l[pivot++]);
        UpdatePath(tree, R_ChildID(i), leaves->l[pivot++]);
    }
    for (int j = n + nodesAmount + 1; j <= m; j++) {  // tworzymy liœcie bêd¹ce w n-1 
        UpdatePath(tree, j, leaves->l[pivot++]);
    }

    return tree;
}

void UpdatePath(vector<node>& tree, short int leaveID, int val) {
    short int pivot = leaveID;
    tree[leaveID].mx = val;   // ustawiam val liœcia

    while (pivot > 1) {   // schodzenie do rodzica, a¿ do korzenia
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

void Replacemax(vector<node>& tree, int newMax) {
    cout << tree[tree[1].mx].mx << " ";
    short int pivot = tree[1].mx;
    short int leaveID = tree[1].mx;
    tree[leaveID].mx = newMax;   // ustawia now¹ wartoœæ val, zamiast max

    while (pivot > 1) {    // schodzenie do rodzica, a¿ do korzenia
        pivot = parentID(pivot);
        if (newMax < tree[tree[pivot].mn].mx) {
            tree[pivot].mx = tree[pivot].mn;
            tree[pivot].mn = leaveID;
            leaveID = tree[pivot].mx;
        }
        else {
            tree[pivot].mx = leaveID;
        }
    }
}

void nReplacemax(vector<node>& tree, array* n) {
  for (int i = 0; i < n->size; i++) Replacemax(tree, n->l[i]);
  cout << endl;
}

void Visualize(vector<node> tree, array* leaves) {
    const int h = treeHeight(leaves->size);

    cout << endl << "Tournament tree: " << endl;
    for (int j = 0; j <= h; j++) {
        for (int i = firstLevelsId(j); i <= lastLevelsId(j); i++) {
            cout << i << "|" << tree[i].mx << ":" << tree[i].mn << "\t\t";
        }
        cout << endl;
    }
}
