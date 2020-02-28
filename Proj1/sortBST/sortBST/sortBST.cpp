#include <stdio.h> 
#include <stdlib.h> 
#include <iostream> 
#include <vector> 
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;
#define MAX_SIZE_OF_ARR 256

struct node {
	int key;
	struct node *l, *r;
};

// Create new node
struct node *newNode(int item) {
	struct node *temp = (struct node *)malloc(sizeof(struct node)); // Allocates appropriate amount of space for node
	temp->key = item;
	temp->l = temp->r = NULL;
	return temp;
}

// Inorder traversal of BST to produce output
void sort(node *root) {
	if (root != NULL) {
		sort(root->l);
		printf("%d ", root->key);
		sort(root->r);
	}
}

// Inserts node into BST recursively
struct node* insertRec(node* node, int key) {
	// Base case, BST at position is empty
	if (node == NULL) {
		return newNode(key);
	}

	// Recursively find correct position of new node (Assumes no duplicate inputs)
	if (key < node->key) { // Traverse left if newNode less than current
		node->l = insertRec(node->l, key);
	}
	else { // Traverse right if newNode greater than current
		node->r = insertRec(node->r, key);
	}

	return node;
}

// Find minimum key recursively in BST (Also used in deleteRec())
struct node * findMinRec(node* node) {
	if (node && node->l != NULL) {
		node = findMinRec(node->l);
	}

	return node;
}

// Find maximum key recursively in BST
struct node * findMaxRec(node* node) {
	if (node && node->r != NULL) {
		node = findMaxRec(node->r);
	}

	return node;
}

void inOrdertoVec(node *node, vector<int> &vec, int i) {
	if (node == NULL) {  // recursion anchor: when the node is null an empty leaf was reached (doesn't matter if it is left or right, just end the method call
		return;
	}

	inOrdertoVec(node->l, vec, i);   // first do every left child tree
	vec.push_back(node->key);      // then write the data in the array
	i++;
	inOrdertoVec(node->r, vec, i);  // do the same with the right child	
}

// Find next node of node in BST inorder vec
void findNextRec(vector<int> vec, int key) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == key) {
			printf("\nNext of node with key %d is %d\n", key, vec[++i]);
			return;
		}
	}
}

// Find next node of node in BST inorder vec
void findPrevRec(vector<int> vec, int key) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == key) {
			printf("\nPrev of node with key %d is %d\n", key, vec[--i]);
			return;
		}
	}
}

// Deletes key and returns new root
struct node* deleteRec(node* root, int key) {
	// Base case, BST at position is empty
	if (root == NULL) {
		return root;
	}

	if (key < root->key) { // Traverse left if newNode less than current
		root->l = deleteRec(root->l, key);
	}
	else if (key > root->key) { // Traverse right if newNode greater than current
		root->r = deleteRec(root->r, key);
	}
	else { // Node to be deleted is found (key == root->key)
		// Case: Node with only one child or no child 
		if (root->l == NULL) {
			struct node *temp = root->r;
			free(root);
			return temp;
		}
		else if (root->r == NULL) {
			struct node *temp = root->l;
			free(root);
			return temp;
		}

		// Case node with two children 
		struct node* temp = findMinRec(root->r); //Get the inorder successor (smallest in the right subtree) 
		root->key = temp->key;  // Copy the inorder successor's content to this node 
		root->r = deleteRec(root->r, temp->key); // Delete the inorder successor 
	}
	return root;
}

int main() {
	struct node *root = NULL; // Initialize root

	root = insertRec(root, 5);
	root = insertRec(root, 7);
	root = insertRec(root, 3);
	root = insertRec(root, 0);
	root = insertRec(root, 1);
	root = insertRec(root, 2);

	printf("Sorted BST using in order traversal: ");
	sort(root);
	cout << endl;

	return 0;
}