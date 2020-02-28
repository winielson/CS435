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
void inorder(node *root) {
	if (root != NULL) {
		inorder(root->l);
		printf("%d ", root->key);
		inorder(root->r);
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

	// INPUT ORDER: numCommands, commands 
	unsigned int numCommands = 0;

	cout << "Commands:\n insert (int)\n delete (int)\n findnext (int)\n findprev (int)\n findmin\n findmax\n\n";
	cout << "Enter number of commands desired: ";
	cin >> numCommands;
	cout << "Enter commands:\n";
	string commands[MAX_SIZE_OF_ARR];

	// Input handling
	for (int i = 0; i < numCommands + 1; i++) {
		getline(cin, commands[i]); // Takes entire line as input string
		if (commands[i].find("insert") != string::npos) { // Checks if delete is in string
			int insVal = 0;
			int q = 0;

			// Split string
			string arr[2];
			stringstream ssin(commands[i]);
			while (ssin.good() && q < 2){
				ssin >> arr[q];
				++q;
			}

			insVal = atoi(arr[1].c_str()); // Converts string to int

			root = insertRec(root, insVal); // assigns new root after insert
			printf("Inorder traversal of the given tree: ");
			inorder(root);
			cout << endl;
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

			delVal = atoi(arr[1].c_str()); // Converts string to int
			deleteRec(root, delVal);
			printf("Current Inorder Traversal of BST: ");
			inorder(root);
			cout << endl;
		}
		else if (commands[i].find("findnext") != string::npos) { // Checks if delete is in string
			vector<int> inOrderArrVec;
			int findVal = 0;
			int q = 0;

			// Split string
			string arr[2];
			stringstream ssin(commands[i]);
			while (ssin.good() && q < 2){
				ssin >> arr[q];
				++q;
			}

			findVal = atoi(arr[1].c_str()); // Converts string to int
			inOrdertoVec(root, inOrderArrVec, 0); // Fill new inorder vec
			findNextRec(inOrderArrVec, findVal);
		}
		else if (commands[i].find("findprev") != string::npos) { // Checks if delete is in string
			vector<int> inOrderArrVec;
			int findVal = 0;
			int q = 0;

			// Split string
			string arr[2];
			stringstream ssin(commands[i]);
			while (ssin.good() && q < 2){
				ssin >> arr[q];
				++q;
			}

			findVal = atoi(arr[1].c_str()); // Converts string to int
			inOrdertoVec(root, inOrderArrVec, 0); // Fill new inorder vec
			findPrevRec(inOrderArrVec, findVal);
		}
		else if (commands[i].find("findmin") != string::npos) { // Checks if delete is in string
			printf("Find min: %d\n", findMinRec(root)->key);
		}
		else if (commands[i].find("findmax") != string::npos) { // Checks if delete is in string
			printf("Find max %d\n", findMaxRec(root)->key);
		}
		else {
			//printf("INVALID COMMAND\n");
		}
	}

	return 0;
}
