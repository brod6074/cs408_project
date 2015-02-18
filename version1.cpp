// Programmer:	Roberto Rodriguez
// Assignment:	Individual Project
// Class:		CS 408, W15
//
// VERSION 1
// Uses structs but does not provide encapsulation. Sets are implemented with linked lists
// using the Node and Set structs.

#include <iostream>
using namespace std;

static const int SET_MAX = 6;

struct Node {
	int val;
	Node *next;
};

struct Set {
	int size;
	Node *head;
	Node *tail;
};

// Set functions
void setAdd(Set *set, int value);
void setClear(Set *set);
void setInit(Set *set);
bool setEqual(Set *set1, Set *set2);
bool setExists(Set *set, int value);
void setPrint(Set *set);

void initializeSets(Set in[], Set out[], Set def[], Set use[], Set successor[]);

int main() {
	Set in[SET_MAX];
	Set out[SET_MAX];
	Set def[SET_MAX];
	Set use[SET_MAX];
	Set successor[SET_MAX];

	initializeSets(in, out, def, use, successor);

	bool change = true; 
	while (change) {
		change = false;
		
		for (int b = 0; b < SET_MAX; b++) {
			cout << "\n\nSET " << (b + 1) << " IN (before): ";
			setPrint(&in[b]);
			cout << "\nSET " << (b + 1) << " OUT (before): ";
			setPrint(&out[b]);

			// old = in[b]
			Set old;
			setInit(&old);
			for (Node *iter = in[b].head; iter != nullptr; iter = iter->next)
				setAdd(&old, iter->val);

			// out[b] = U in[p] for each successor p of b
			for (Node *succIter = successor[b].head; succIter != nullptr; succIter = succIter->next) {
				int p = succIter->val;
				for (Node *inIter = in[p].head; inIter != nullptr; inIter = inIter->next) {
					setAdd(&out[b], inIter->val);
				}
			}

			// in[b] = use[b] U (out[b] - def[b])
			setClear(&in[b]);
			for (Node *iter = use[b].head; iter != nullptr; iter = iter->next)
				setAdd(&in[b], iter->val);

			for (Node *iter = out[b].head; iter != nullptr; iter = iter->next) {
				if (!setExists(&def[b], iter->val))
					setAdd(&in[b], iter->val);
			}


			// if (in[b] != old)
			//		change = true
			if (!setEqual(&in[b], &old))
				change = true;

			setClear(&old);

			cout << "\nSET " << (b + 1) << " IN (after): ";
			setPrint(&in[b]);
			cout << "\nSET " << (b + 1) << " OUT (after): ";
			setPrint(&out[b]);
		}
		cout << "\n==================================";
	}

	// Deallocate memory before exiting
	for (int b = 0; b < SET_MAX; b++) {
		setClear(&in[b]);
		setClear(&out[b]);
		setClear(&def[b]);
		setClear(&use[b]);
		setClear(&successor[b]);
	}

	cout << endl;
	return 0;
}

// Add value to the set
void setAdd(Set *set, int value) {
	// return if value already exists in the set
	if (setExists(set, value))
		return;

	Node *newNode = new Node();
	newNode->val = value;
	newNode->next = nullptr;

	if (set->size == 0) {
		set->head = set->tail = newNode;
	} else {
		set->tail->next = newNode;
		set->tail = newNode;
	}

	set->size++;
}

// Clears contents of set
void setClear(Set *set) {
	if (set->size == 0)
		return;

	for (Node *iter = set->head; iter != nullptr; iter = set->head) {
		set->head = set->head->next;
		delete iter;
	}

	set->head = set->tail = nullptr;
	set->size = 0;
}

// Returns true if the sets are equal. Returns false otherwise
bool setEqual(Set *set1, Set *set2) {
	if (set1->size != set2->size)
		return false;

	Node *iter1 = set1->head;
	Node *iter2 = set2->head;
	while ((iter1 != nullptr) && (iter2 != nullptr)) {
		if (iter1->val != iter2->val)
			return false;
		iter1 = iter1->next;
		iter2 = iter2->next;
	}

	return true;
}

// Returns true is value exists in the set. False otherwise
bool setExists(Set *set, int value) {
	for (Node *iter = set->head; iter != nullptr; iter = iter->next) {
		if (value == iter->val)
			return true;
	}

	return false;
}

// Initializes pointers to null and values to 0
void setInit(Set *set) {
	set->head = set->tail = nullptr;
	set->size = 0;
}

// Prints out the set contents
void setPrint(Set *set) {
	for (Node *iter = set->head; iter != nullptr; iter = iter->next) {
		cout << (char)iter->val << " ";
	}
}

// Initializes the contents of all the sets according to the project specification.
void initializeSets(Set in[], Set out[], Set def[], Set use[], Set successor[]) {

	// Initialize all sets to empty
	for (int b = 0; b < SET_MAX; b++) {
		setInit(&in[b]);
		setInit(&out[b]);
		setInit(&def[b]);
		setInit(&use[b]);
		setInit(&successor[b]);
	}

	// Block 1
	setAdd(&def[0], 'a');
	setAdd(&def[0], 'b');
	setAdd(&successor[0], 1);

	// Block 2
	setAdd(&use[1], 'a');
	setAdd(&use[1], 'b');
	setAdd(&def[1], 'c');
	setAdd(&def[1], 'd');
	setAdd(&successor[1], 2);
	setAdd(&successor[1], 4);

	// Block 3
	setAdd(&use[2], 'b');
	setAdd(&use[2], 'd');
	setAdd(&successor[2], 3);
	setAdd(&successor[2], 4);

	// Block 4
	setAdd(&use[3], 'a');
	setAdd(&use[3], 'b');
	setAdd(&use[3], 'e');
	setAdd(&def[3], 'd');
	setAdd(&successor[3], 2);

	// Block 5
	setAdd(&use[4], 'a');
	setAdd(&use[4], 'b');
	setAdd(&use[4], 'c');
	setAdd(&def[4], 'e');
	setAdd(&successor[4], 1);
	setAdd(&successor[4], 5);

	// Block 6
	setAdd(&use[5], 'b');
	setAdd(&use[5], 'd');
	setAdd(&def[5], 'a');
}