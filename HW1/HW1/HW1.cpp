#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <queue> 
#define MAX_SIZE_OF_ARR 256
using namespace std;

class Node {
public:
	int data;
	Node* l;
	Node* r;

	Node(int data) //Constructor
	{
		this->data = data;
		this->l = NULL;
		this->r = NULL;
	}
};

Node* newNode(int data) {
	/*
	malloc() is a standard library function in C that allocates memory of size equal to the
	size of newnode structure in the heap region during runtime and returns a void pointer to that location.
	*/
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->l = node->r = NULL;
	return (node);
}

//fromArray which creates nodes for a complete tree represented by the given array.
Node* fromArray(int arr[], Node* root, int size, int i) {
	if (i < size) {
		Node* temp = newNode(arr[i]);
		root = temp;

		root->l = fromArray(arr, root->l, size, 2 * i + 1); // Insert left child 
		root->r = fromArray(arr, root->r, size, 2 * i + 2); // Insert right child 
	}
	return root;
}

// toArray which returns the array representation of the complete tree.
Node* toArray(Node* root) {
	return root;
}

//isBSTUtil used to recursively traverse the BST
bool isBSTUtil(struct Node* root, Node* &prev)
{
	// Traverse the tree in inorder fashion (left, root, right) and keep track of prev node 
	if (root) {
		if (!isBSTUtil(root->l, prev)) {
			return false;
		}

		// Allows only distinct valued nodes  
		if (prev != NULL && root->data <= prev->data) {
			return false;
		}

		prev = root;

		return isBSTUtil(root->r, prev);
	}

	return true;
}

//isBST which returns true if the complete tree is a Binary Search Tree.
bool isBST(Node* root) {
	Node *prev = NULL;
	return isBSTUtil(root, prev);
}

//preOrder which prints a pre-order traversal of the tree. (root, left, right)
void preOrder(Node* node) {
	if (node == NULL)
		return;

	cout << node->data << " "; // 1. Print node data
	preOrder(node->l); // 2. Recursively check left node tree
	preOrder(node->r); // 3. Recursively check right node tree
}

//postOrder which prints a post-order traversal of the tree. (left, right, root)
void postOrder(Node* node) {
	if (node == NULL)
		return;

	postOrder(node->l); // 3. Recursively check left node tree
	postOrder(node->r); // 2. Recursively check right node tree
	cout << node->data << " "; // 3. Print node data
}

//bSearch: recursive function that performs binary search, and prints number of nodes visited
void bSearch(Node* node, int find, int numVisited) {
	// If a match, print number of nodes visited
	if (node->data == find) {
		numVisited++;
		printf("%d", numVisited);
	}
	// Checks right child if find is greater than node->data
	else if (node->data < find) {
		numVisited++;
		bSearch(node->r, find, numVisited);
	}
	// Checks left child if find is less than node->data
	else if (node->data > find) {
		numVisited++;
		bSearch(node->l, find, numVisited);
	}
	else {
		printf("No node with data %d in BST", find);
	}
}

//levelOrder: iterative function that performs breadth first/level order traversal, and prints number of nodes visited
void levelOrder(Node* root, int find, int numVisited) {
	if (root == NULL) {
		return;
	}

	// Creates queue to perform BFS
	queue<Node *> q;
	q.push(root); // Push root into queue

	// Iteratively check nodes level by level
	while (q.empty() == false)
	{
		Node *node = q.front(); // Print front of queue and remove it from queue 

		if (node->data == find) { // Breaks loop when find is found
			numVisited++;
			printf("%d\n", numVisited);
			break;
		}

		q.pop(); // Pops if not front node
		numVisited++;

		if (node->l != NULL) { // Push left child into queue
			q.push(node->l);
		}
		if (node->r != NULL) { // Push right child into queue
			q.push(node->r);
		}
	}
}

//numNodesInLookup: determines which lookup to use, and prints # of nodes visited in lookup
void numNodesInLookup(Node* root, int find) {
	if (isBST(root)) {
		// BINARY SEARCH HERE
		bSearch(root, find, 0);
	}
	else {
		// Level order traversal/breadth first traversal
		levelOrder(root, find, 0);
	}
}

int main() {
	// INPUT ORDER: numNodes, array, numCommands, commands 
	unsigned int numNodes, numCommands = 0;
	cin >> numNodes;

	int treeVals[MAX_SIZE_OF_ARR];
	for (int i = 0; i < numNodes; i++) {
		cin >> treeVals[i];
	}

	/* Displays inputed array
	for (int i = 0; i < numNodes; i++) {
	cout << treeVals[i] << " ";
	}
	printf("\n");
	*/

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

	Node* root = (Node*)malloc(sizeof(Node)); //Init root node
	// Create complete tree from array
	root = fromArray(treeVals, root, numNodes, 0); // Passes arr[], itself, size of arr, and iteration

	// Input handling
	for (int i = 0; i < numCommands + 1; i++) {
		if (commands[i] == "toArray") {
			//int toArr[numNodes] = toArray(root);
			for (int j = 0; j < numNodes; j++) {
				cout << treeVals[j] << " ";
			}
			printf("\n");
		}
		else if (commands[i] == "isBST") {
			if (isBST(root)) {
				cout << "true\n";
			}
			else {
				cout << "false\n";
			}
		}
		else if (commands[i] == "preOrder") {
			preOrder(root);
			printf("\n");
		}
		else if (commands[i] == "postOrder") {
			postOrder(root);
			printf("\n");
		}
		else if (commands[i].find("numNodesInLookup") != string::npos) { // Checks if numNodesInLookup is in string
			int find = 0;
			int q = 0;

			// Split string
			string arr[2];
			stringstream ssin(commands[i]);
			while (ssin.good() && q < 2){
				ssin >> arr[q];
				++q;
			}
			//cout << endl << arr[1] << endl;
			find = atoi(arr[1].c_str()); // Converts string to int
			//printf("find = %d", find);
			numNodesInLookup(root, find);
		}
	}

	return 0;
}