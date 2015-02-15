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

struct Block {
	Set in;
	Set out;
	Set def;
	Set use;
	Set successor;
};

// Set functions
bool setExists(Set *set, int value);
void setAdd(Set *set, int value);

int main() {

	Set set;
	set.head = set.tail = NULL;
	set.size = 0;
	setAdd(&set, 1);
	setAdd(&set, 2);
	setAdd(&set, 1);
	setAdd(&set, 3);

	return 0;
}

bool setExists(Set *set, int value) {
	for (Node *iter = set->head; iter != NULL; iter = iter->next) {
		if (value == iter->val)
			return true;
	}

	return false;
}

void setAdd(Set *set, int value) {
	// return if value already exists in the set
	if (setExists(set, value))
		return;

	Node *newNode = new Node();
	newNode->val = value;
	newNode->next = NULL;

	if (set->size == 0) {
		set->head = set->tail = newNode;
	} else {
		set->tail->next = newNode;
		set->tail = newNode;
	}

	set->size++;
}