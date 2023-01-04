#include <iostream>
#include "Array.hpp"
#include "BruteForce.hpp"
using namespace std;

int main() {
  array arr; 
  arr = NewRandomArray(6);
  getNMaxValues(&arr, 3);
}
