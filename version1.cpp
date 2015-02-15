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
bool setEqual(Set *set1, Set *set2);

void initializeBlocks(Block blocks[]);

int main() {

	//Block blocks[SET_MAX];
	Set set1, set2;
	set1.head = set1.tail = NULL;
	set1.size = 0;
	set2.head = set2.tail = NULL;
	set2.size = 0;
	
	setAdd(&set1, 1);
	//setAdd(&set2, 2);

	if (setEqual(&set1, &set2))
		cout << "The sets are equal" << endl;
	else
		cout << "The sets are not equal" << endl;

	//initializeBlocks(blocks);

	return 0;
}

void initializeBlocks(Block blocks[]) {

	for (int i = 0; i < SET_MAX; i++) {
		blocks[i].in.head = blocks[i].in.tail = NULL;
		blocks[i].in.size = 0;
		blocks[i].out.head = blocks[i].out.tail = NULL;
		blocks[i].out.size = 0;
		blocks[i].def.head = blocks[i].def.tail = NULL;
		blocks[i].def.size = 0;
		blocks[i].use.head = blocks[i].use.tail = NULL;
		blocks[i].use.size = 0;
		blocks[i].successor.head = blocks[i].successor.tail = NULL;
		blocks[i].successor.size = 0;
	}

	// BLOCK B1
	setAdd(&blocks[0].def, (int) 'a');
	setAdd(&blocks[0].def, (int) 'b');
	setAdd(&blocks[0].successor, (int) 1);

	// BLOCK B2
	setAdd(&blocks[1].use, (int) 'a');
	setAdd(&blocks[1].use, (int) 'b');
	setAdd(&blocks[1].def, (int) 'c');
	setAdd(&blocks[1].def, (int) 'd');
	setAdd(&blocks[1].successor, (int) 2);
	setAdd(&blocks[1].successor, (int) 4);

	// BLOCK B3
	setAdd(&blocks[2].use, (int) 'b');
	setAdd(&blocks[2].successor, (int) 3);
	setAdd(&blocks[2].successor, (int) 4);

	// BLOCK B4
	setAdd(&blocks[3].use, (int) 'a');
	setAdd(&blocks[3].use, (int) 'b');
	setAdd(&blocks[3].def, (int) 'd');
	setAdd(&blocks[3].successor, (int) 2);

	// BLOCK B5
	setAdd(&blocks[4].use, (int) 'a');
	setAdd(&blocks[4].use, (int) 'c');
	setAdd(&blocks[4].def, (int) 'e');
	setAdd(&blocks[4].successor, (int) 1);
	setAdd(&blocks[4].successor, (int) 5);

	// BLOCK B6
	setAdd(&blocks[5].use, (int) 'b');
	setAdd(&blocks[5].use, (int) 'd');
	setAdd(&blocks[5].def, (int) 'a');
}

// Returns true is value exists in the set. False otherwise
bool setExists(Set *set, int value) {
	for (Node *iter = set->head; iter != NULL; iter = iter->next) {
		if (value == iter->val)
			return true;
	}

	return false;
}

// Add value to the set
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

// Returns true if the sets are equal. Returns false otherwise
bool setEqual(Set *set1, Set *set2) {
	if (set1->size != set2->size)
		return false;

	Node *iter1 = set1->head;
	Node *iter2 = set2->head;
	while ((iter1 != NULL) && (iter2 != NULL)) {
		if (iter1->val != iter2->val)
			return false;
		iter1 = iter1->next;
		iter2 = iter2->next;
	}

	return true;
}