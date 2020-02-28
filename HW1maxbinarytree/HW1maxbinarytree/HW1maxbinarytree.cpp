#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <climits> 
#define MAX_SIZE_OF_ARR 256
#define MAX_SIZE_OF_HEAP 256
using namespace std;

// Prototypes
// Swap two elements by position
void swap(int *x, int *y); 

class MaxHeap {
	int *harr; // Pointer to heap array
	int capacity; // Maximum possible size of heap
	int size; // Current number of elements in max heap 
public:
	// Constructor 
	MaxHeap(int capacity);

	// Returns the size of heap
	int getSize() {
		return size;
	}

	// Returns the max key
	int maxLookup() {
		return harr[0];
	}

	// Extracts the max value (root)
	int extractMax();

	// Inserts a new key 
	void ins(int k);

	// Increases value of key at index to new_val, assuming new_val is larger than harr[i]. Used for deleting.
	void increase(int i, int new_val);

	// Deletes a key stored at index i 
	void del(int i);

	// Heapify a tree given the index in harr
	void MaxHeapify(int i);

	// Return parent of key
	int parent(int i) {
		return (i - 1) / 2;
	}

	// Return index of left child of node at index i 
	int l(int i) {
		return (2 * i + 1);
	}

	// Return index of right child of node at index i 
	int r(int i) {
		return (2 * i + 2);
	}
};

// Constructor: Builds a heap from a given array capacity
MaxHeap::MaxHeap(int capacity) {
	size = 0;
	capacity = capacity;
	harr = new int[capacity];
}

// extractMax: Removes max element
int MaxHeap::extractMax() {
	if (size <= 0) {
		return INT_MIN; // INT_MIN is smallest int possible
	}
	if (size == 1) {
		size--;
		return harr[0];
	}

	// Store the maximum value, and remove it from heap 
	int root = harr[0];
	harr[0] = harr[size - 1]; // swap root with max element
	size--;
	MaxHeapify(0);

	return root;
}

// Inserts a new key
void MaxHeap::ins(int k) {
	// Insert the new key at the end of heap arr
	size++;
	int i = size - 1;
	harr[i] = k;

	// Fix the max heap property if it is violated 
	while (i != 0 && harr[i] > harr[parent(i)]) {
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

// Increases value of key at index to new_val, assuming new_val is larger than harr[i]. Used for deleting.
void MaxHeap::increase(int i, int new_val) {
	harr[i] = new_val;
	while (i != 0 && harr[i] > harr[parent(i)]) { // Swaps keys until they are in correct positions
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

// // Deletes a key stored at index i 
void MaxHeap::del(int i) {
	increase(i, INT_MAX); //Increases key to maximum int value to guarantee it to be root
	extractMax(); // Removes it
}

// Recursively heapifies a tree at index 
void MaxHeap::MaxHeapify(int i) {

	int largest = i; // Used to find root
	if (l(i) < size && harr[l(i)] > harr[i]) {
		largest = l(i);
	}
	if (r(i) < size && harr[r(i)] > harr[largest]) {
		largest = r(i);
	}
	if (largest != i) {
		swap(&harr[i], &harr[largest]);
		MaxHeapify(largest);
	}
}

// Swap two elements by position
void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

int main() {
	// INPUT ORDER: numCommands, commands 
	unsigned int numCommands = 0;

	cin >> numCommands;
	string commands[MAX_SIZE_OF_ARR];
	for (int i = 0; i < numCommands + 1; i++) {
		getline(cin, commands[i]);
	}

	/* Displays inputed command array
	for (int i = 0; i < numNodes; i++) {
	cout << commands[i] << " ";
	}
	printf("\n");
	*/

	// Init MaxHeap
	MaxHeap heap(MAX_SIZE_OF_HEAP);

	// Input handling
	for (int i = 0; i < numCommands + 1; i++) {
		if (commands[i] == "size") {
			cout << heap.getSize() << "\n";
		}
		else if (commands[i] == "maxLookup") {
			cout << heap.maxLookup() << "\n";
		}
		else if (commands[i] == "extractMax") {
			heap.extractMax();
		}
		else if (commands[i].find("insert") != string::npos) { // Checks if insert is in string
			int insVal = 0;
			int q = 0;

			// Split string
			string arr[2];
			stringstream ssin(commands[i]);
			while (ssin.good() && q < 2){
				ssin >> arr[q];
				++q;
			}
			//cout << endl << arr[1] << endl;
			insVal = atoi(arr[1].c_str()); // Converts string to int
			//printf("find = %d", find);
			heap.ins(insVal);
		}
		else if (commands[i].find("delete") != string::npos) { // Checks if delete is in string
			int delVal = 0;
			int q = 0;

			// Split string
			string arr[2];
			stringstream ssin(commands[i]);
			while (ssin.good() && q < 2){
				ssin >> arr[q];
				++q;
			}
			//cout << endl << arr[1] << endl;
			delVal = atoi(arr[1].c_str()); // Converts string to int
			//printf("find = %d", find);
			heap.del(delVal);
		}
	}

	return 0;
}