// author: Nikodem Panknin
// title: Basic array library

#pragma once
#include <random>
#include <iostream>
using namespace std;


struct array { int* l; short int size; };   // struktura tablic 

array NewRandomArray(short int n);
void printArray(array* arr);

array NewRandomArray(short int n) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> rd(1, 1000000);

    array leaves;
    leaves.size = n;
    leaves.l = new int[leaves.size];
    for (int i = 0; i < leaves.size; i++) leaves.l[i] = rd(rng);

    return leaves;
}

void printArray(array* arr) {
    cout << "Array[0.."<< arr->size - 1 << "]: ";
    for (int i = 0; i < arr->size; i++) cout << arr->l[i] << " ";
    cout << endl;
}
