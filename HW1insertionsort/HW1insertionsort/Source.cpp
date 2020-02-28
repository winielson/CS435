#include <stdio.h>
#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <queue> 
#define MAX_SIZE_OF_ARR 256
using namespace std;

/* Link list node */
struct Node
{
	int year;
	string first, last;
	struct Node* next;
};

/* function prototypes */
Node* SortedMerge(Node* a, Node* b);
void FrontBackSplit(Node* source,
	Node** frontRef, Node** backRef);

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(Node** headRef)
{
	Node* head = *headRef;
	Node* a;
	Node* b;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
Node* SortedMerge(Node* a, Node* b)
{
	Node* result = NULL;

	/* Base cases */
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	/* Pick either a or b, and recur */
	if (a->data <= b->data) {
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else {
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
and return the two lists using the reference parameters.
If the length is odd, the extra node should go in the front list.
Uses the fast/slow pointer strategy. */
void FrontBackSplit(Node* source,
	Node** frontRef, Node** backRef)
{
	Node* fast;
	Node* slow;
	slow = source;
	fast = source->next;

	/* Advance 'fast' two nodes, and advance 'slow' one node */
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	/* 'slow' is before the midpoint in the list, so split it in two
	at that point. */
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

/* Function to print nodes in a given linked list */
void printList(Node* node)
{
	while (node != NULL) {
		cout << node->data << " ";
		node = node->next;
	}
}

/* A utility function to insert a node at the beginning of linked list */
void push(struct Node** head_ref, string f, string l, int y)
{
	/* allocate node */
	struct Node* new_node = new Node;

	/* put in the data  */
	new_node->first = f;
	new_node->last = l;
	new_node->year = y;

	/* link the old list off the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

int main() {
	// INPUT ORDER: numStudents, commands 
	unsigned int numStudents = 0;
	cin >> numStudents; // size of record array

	struct Node *head = NULL; // Init head of linked list

	// Construct student record array
	string recordarr[MAX_SIZE_OF_ARR];
	for (int i = 0; i < numStudents + 1; i++) {
		getline(cin, recordarr[i]);
		string first, last;
		int year = 0;
		int q = 0;

		// Split string
		istringstream ss(recordarr[i]);
		ss >> first;
		ss >> last;
		ss >> year;

		//cout << first << " " << last << " " << year << endl;

		if (year) {
			push(&head, first, last, year); // Pushes node into linked list
		}

		//push(&head, first, last, year); // Pushes node into linked list
	}
	//cout << endl;

	//printList(head);

	mergeSort(&head);
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	return 0;
}
