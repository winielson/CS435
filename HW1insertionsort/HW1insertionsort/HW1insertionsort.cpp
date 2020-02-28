#include "stdafx.h"
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

/* Function to print linked list */
void printList(struct Node *head)
{
	struct Node *temp = head;
	while (temp != NULL)
	{
		cout << temp->first << " " << temp->last << " " << temp->year << endl;
		// printf("%s %s %d\n", temp->first, temp->last, temp->year);
		temp = temp->next;
	}
}

// Function to insert a given node in a sorted linked list 
void sortedInsert(struct Node**, struct Node*, int, int);

// function to sort a singly linked list using insertion sort 
void insertionSort(struct Node **head_ref, int unsortedsize) {
	int sortedsize = 0;
	// Initialize sorted linked list 
	struct Node *sorted = NULL;

	// Traverse the given linked list and insert every 
	// node to sorted 
	struct Node *current = *head_ref;
	while (current != NULL)
	{

		// Store next for next iteration 
		struct Node *next = current->next;

		// insert current in sorted linked list 
		sortedsize++;
		sortedInsert(&sorted, current, sortedsize, unsortedsize);

		//
		//printf("ss: %d, us: %d\n", sortedsize, unsortedsize);

		// Update current 
		current = next;


		/*
		struct Node *temp = sorted;
		while (temp != NULL) //Gets size of linked list
		{
		sortedsize++;
		temp = temp->next;
		}*/
		/*Print each iteration of inserted
		if(sortedsize == unsortedsize) {
		printList(sorted);
		cout << endl;
		}*/
	}

	//printList(sorted);
	//cout << endl;

	// Update head_ref to point to sorted linked list 
	*head_ref = sorted;
}

/* function to insert a new_node in a list. Note that this
function expects a pointer to head_ref as this can modify the
head of the input linked list (similar to push())*/
void sortedInsert(struct Node** head_ref, struct Node* new_node, int sortedsize, int unsortedsize)
{
	struct Node* current;
	/* Special case for the head end */
	if (*head_ref == NULL || (*head_ref)->year < new_node->year)
		//if (*head_ref == NULL || (*head_ref)->first >= new_node->first)
	{
		//cout << "\nIn loop 1 adding head to sorted arr" << endl;
		new_node->next = *head_ref;
		*head_ref = new_node;
		if (sortedsize == unsortedsize) {
			printList(*head_ref);
			cout << endl;
		}
	}
	else if (*head_ref == NULL || (*head_ref)->year <= new_node->year)
		//if (*head_ref == NULL || (*head_ref)->first >= new_node->first)
	{
		//cout << "\nIn loop 1 adding head to sorted arr" << endl;
		new_node->next = *head_ref;
		*head_ref = new_node;
		if (sortedsize == unsortedsize) {
			printList(*head_ref);
			cout << endl;
		}
	}
	else if (*head_ref == NULL || (*head_ref)->year <= new_node->year)
		//if (*head_ref == NULL || (*head_ref)->first >= new_node->first)
	{
		//cout << "\nIn loop 1 adding head to sorted arr" << endl;
		new_node->next = *head_ref;
		*head_ref = new_node;
		if (sortedsize == unsortedsize) {
			printList(*head_ref);
			cout << endl;
		}
	}
	else
	{
		// cout << "In else\n" << endl;
		// Locate the node before the point of insertion 
		current = *head_ref;
		while (current->next != NULL && current->next->year < new_node->year)
		{
			current = current->next;
			if (sortedsize == unsortedsize) {
				printList(*head_ref);
				cout << endl;
			}
			//printList(*head_ref);
			//cout << endl;
			//cout << "\nIn loop 2"<< endl;
		}
		// Compares first if year is same, swaps if left node is comes after right node alphabetically
		while (current->year == new_node->year && current->first > new_node->first)
		{
			current = current->next;
			if (sortedsize == unsortedsize) {
				printList(*head_ref);
				cout << endl;
			}
			//cout << "\nIn loop 3"<< endl;
		}
		// Compares last if year and first are same, swaps if left node is comes after right node alphabetically
		while (current->year == new_node->year && current->first == new_node->first && current->last > new_node->last)
		{
			current = current->next;
			if (sortedsize == unsortedsize) {
				printList(*head_ref);
				cout << endl;
			}
			//cout << "\nIn loop 4"<< endl;
		}
		new_node->next = current->next;
		current->next = new_node;
		if (sortedsize == unsortedsize) {
			printList(*head_ref);
			cout << endl;
		}
	}
}

/* BELOW FUNCTIONS ARE JUST UTILITY TO TEST sortedInsert */

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


/* Given a reference (pointer to pointer) to the head
of a list and an int, appends a new node at the end  */
void append(struct Node** head_ref, string f, string l, int y)
{
	/* 1. allocate node */
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	struct Node *last = *head_ref;  /* used in step 5*/

	/* 2. put in the data  */
	new_node->first = f;
	new_node->last = l;
	new_node->year = y;

	/* 3. This new node is going to be the last node, so make next
	of it as NULL*/
	new_node->next = NULL;

	/* 4. If the Linked List is empty, then make the new node as head */
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	/* 5. Else traverse till the last node */
	while (last->next != NULL)
		last = last->next;

	/* 6. Change the next of last node */
	last->next = new_node;
	return;
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
			append(&head, first, last, year); // Pushes node into linked list
		}

		//push(&head, first, last, year); // Pushes node into linked list
	}
	//cout << endl;

	//printList(head);

	insertionSort(&head, numStudents);

	//printList(head);

	//Node* recArr[MAX_SIZE_OF_ARR];

	/* Displays inputed command array
	for (int i = 0; i < numNodes; i++) {
	cout << recordarr[i] << " ";
	}
	printf("\n");
	*/

	//insertionSort(recordarr, numStudents); 

	return 0;
}