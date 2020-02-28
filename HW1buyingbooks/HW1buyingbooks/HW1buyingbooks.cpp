#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

// Merges two subarrays of arr[]. 
void merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int lSize = m - l + 1; // Size of left subarray
	int rSize = r - m; // Size of right subarray

	// Create temporary arrays
	int L[lSize], R[rSize];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < lSize; i++) {
		L[i] = arr[l + i];
	}
	for (j = 0; j < rSize; j++) {
		R[j] = arr[m + 1 + j];
	}

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < lSize && j < rSize) {
		if (L[i] >= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < lSize) {
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < rSize) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
	if (l < r) {
		// Pivot of middle of array
		int m = (l + r) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		// Merge the two subarrays
		merge(arr, l, m, r);
	}
}

int main() {
	int numBooks;
	cin >> numBooks;

	int cost = 0;
	int bookPrices[10];
	for (int i = 0; i < numBooks; ++i) {
		int price;
		cin >> price;
		bookPrices[i] = price;
	}

	mergeSort(bookPrices, 0, numBooks); // Merge sort in descending order

	int c = 0; // 
	// Loops through array from de
	for (int i = 0; i < numBooks; i++) {
		if (c != 2){ // don't add price of book if we've added 2 since the last freebie
			cost += bookPrices[i + 1];
			c++;
		}
		else {
			c = 0;
		}
	}
	cout << cost << endl;
	return 0;
}