// author: Nikodem Panknin
// title: Brute force n-max values

#include <iostream>
#include "Array.hpp"
using namespace std;


void getMaxValue(array* arr);
void getNMaxValues(const array* arr, int n);


void getMaxValue(array* arr) {
  int max = 0;
  int index = 0;

  for (int i = 0; i < arr->size; i++) {
    if (max < arr->l[i]) {
      max = arr->l[i];
      index = i;
    }
  }

  cout << arr->l[index] << " ";
  arr->l[index] = 0;
}

void getNMaxValues(const array* arr, int n) {
  array* newArr = new array;
  newArr->l = arr->l;
  newArr->size = arr->size;
  for (int i = 0; i < n; i++) getMaxValue(newArr);
  cout << endl;
}

