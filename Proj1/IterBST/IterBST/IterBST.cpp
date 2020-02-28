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

// Inserts node into BST Iteratively
struct node* insertIter(node* root, int key) {
	node* newnode = newNode(key); // Create new node with give key
	node* x = root; // Pointer to start traversing from root
	node* y = NULL; // Pointer used to keep trailing pointer of x

	// Iteratively traverse nodes
	while (x != NULL) {
		y = x;
		if (key < x->key) { // Check left child if key less than x (current node)
			x = x->l;
		}
		else { // Check right child if key greater than x (current node)
			x = x->r;
		}
	}

	// Assign position of newNode
	if (y == NULL) { // Base case, root is NULL
		y = newnode;
	}
	else if (key < y->key) { // Left child if new key is less than y
		y->l = newnode;
	}
	else { // Right child if new key is greater than y
		y->r = newnode;
	}

	return y;
}

// Find minimum key Iteratively in BST (Also used in deleteIter())
struct node * findMinIter(node* node) {
	struct node* temp = node;

	// Iteratively loop left
	while (temp && temp->l != NULL)
		temp = temp->l;

	return temp;
}

// Find maximum key Iteratively in BST
struct node * findMaxIter(node* node) {
	struct node* temp = node;

	// Iteratively loop right
	while (temp && temp->r != NULL)
		temp = temp->r;

	return temp;
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
void findNextIter(vector<int> vec, int key) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == key) {
			printf("\nNext of node with key %d is %d\n", key, vec[++i]);
			return;
		}
	}
}

// Find next node of node in BST inorder vec
void findPrevIter(vector<int> vec, int key) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == key) {
			printf("\nPrev of node with key %d is %d\n", key, vec[--i]);
			return;
		}
	}
}

/*FIX ITERATIVE METHOD*/
// Deletes key and returns new root
node* deleteIter(node* root, int key) {
	/*
	//node* newnode = newNode(key); // Create new node with give key
	node* x = root; // Pointer to start traversing from root
	node* y = NULL; // Pointer used to keep trailing pointer of x
	//node* z = NULL; // Parent of y

	// Iteratively find node
	while (x != NULL) {
		y = x;
		if (key < x->key) { // Check left child if key less than x (current node)
			x = x->l;
			//z = y;
		}
		else { // Check right child if key greater than x (current node) or breaks loop when both children are null
			x = x->r;
			//z = y;
		}
	}

	// y is the node to be deleted
	if (y->l == NULL && y->r == NULL) { // Both children are empty
		//delete y;
		free(y);
		return;
	}
	else if (y->l == NULL) { // Left child is empty
		struct node *temp = y->r;
		delete y;
		//free(y);
		return;
	}
	else if (y->r == NULL) { // Right child is empty
		struct node *temp = y->l;
		//delete y;
		free(y);
		return;
	}
	else { // Case: node with two children 
		node* succParent = y->r;

		// Find successor 
		node* succ = y->r;
		while (succ->l != NULL) {
			succParent = succ;
			succ = succ->l;
		}

		succParent->l = succ->r;

		// Copy Successor Data to root 
		y->key = succ->key;

		// Delete Successor and return root 
		//delete succ;
		free(y);
		return;
	}
	
	//return y;
	*/

	/*RECURSIVE METHOD FIX ITERATIVE ABOVE*/
	// Base case, BST at position is empty
	if (root == NULL) {
		return root;
	}

	if (key < root->key) { // Traverse left if newNode less than current
		root->l = deleteIter(root->l, key);
	}
	else if (key > root->key) { // Traverse right if newNode greater than current
		root->r = deleteIter(root->r, key);
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
		struct node* temp = findMinIter(root->r); //Get the inorder successor (smallest in the right subtree) 
		root->key = temp->key;  // Copy the inorder successor's content to this node 
		root->r = deleteIter(root->r, temp->key); // Delete the inorder successor 
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

			if (root == NULL) {
				root = insertIter(root, insVal); // assigns new root after insert
			}
			else
				insertIter(root, insVal);
			printf("Inorder traversal of the given tree: ");
			if (root != NULL)
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
			deleteIter(root, delVal);
			printf("Current Inorder Traversal of BST: ");
			cout << root->key;
			if (root < 0) {
				root = NULL;
				inorder(root);
			}
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
			findNextIter(inOrderArrVec, findVal);
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
			findPrevIter(inOrderArrVec, findVal);
		}
		else if (commands[i].find("findmin") != string::npos) { // Checks if delete is in string
			printf("Find min: %d\n", findMinIter(root)->key);
		}
		else if (commands[i].find("findmax") != string::npos) { // Checks if delete is in string
			printf("Find max %d\n", findMaxIter(root)->key);
		}
		else {
			//printf("INVALID COMMAND\n");
		}
	}

	return 0;
}
