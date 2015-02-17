// Programmer:	Roberto Rodriguez
// Assignment:	Individual Project
// Class:		CS 408, W15
//
// VERSION 2

#include <iostream>
#include "Set.h"
using namespace std;

static const int SET_MAX = 6;

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
        for (int b = 0; b < SET_MAX; b++) {

        }
    }

    return 0;
}

void initializeSets(Set in[], Set out[], Set def[], Set use[], Set successor[]) {
    // Block 1
    def[0].insert('a');
    def[0].insert('b');
    successor[0].insert(1);

	// Block 2
    use[1].insert('a');
    use[1].insert('b');
    def[1].insert('c');
    def[1].insert('d');
    successor[1].insert(2);
    successor[1].insert(4);

	// Block 3
    use[2].insert('b');
    use[2].insert('d');
    successor[2].insert(3);
    successor[2].insert(4);

	// Block 4
    use[3].insert('a');
    use[3].insert('b');
    use[3].insert('e');
    def[3].insert('d');
    successor[3].insert(2);

	// Block 5
    use[4].insert('a');
    use[4].insert('b');
    use[4].insert('c');
    def[4].insert('e');
    successor[4].insert(1);
    successor[4].insert(5);

	// Block 6
    use[5].insert('b');
    use[5].insert('d');
    def[5].insert('a');
}
