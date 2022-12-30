#include <iostream>
#include <math.h>
#define CALC(X) X*X;
#define AL(tree_height) (int)pow(2, tree_height + 1) - 1;

using namespace std;


int main() {
  cout << AL(3);
}
