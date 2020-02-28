#include <stdio.h> 
#include <stdlib.h> 
#include <iostream> 
#include <algorithm>
using namespace std;
#define MAX_SIZE_OF_ARR 256

void getRandomArray(int n) {
	int randArr[n];
	for (int i = 0; i < n; i++) {
		randArr[i] = rand();
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", randArr[i]);
	}
}

void getSortedArray(int n) {
	int sortArr[n];
	for (int i = 0; i < n; i++) {
		sortArr[i] = n - i;
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", sortArr[i]);
	}
}

int main() {
	int n = 6;

	cout << "Random array: ";
	getRandomArray(n);
	cout << endl << "Sorted array: ";
	getSortedArray(n);
}