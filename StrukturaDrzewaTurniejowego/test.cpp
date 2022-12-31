#include <iostream>
#include <vector>

using namespace std;

struct tree {int mx; int mn;};

vector<tree> tp() {
  vector<tree> t;
  tree nt {2, 3};
  t.push_back(nt);
  return t;
}

int main () {
 vector<tree> tak = tp();
 cout << tak[0].mx << endl << tak[0].mn ;

  int a = 20;
  do {
    a = int(a/3);
    cout <<a <<endl;
  } while (a > 1);
 return 0;
}

