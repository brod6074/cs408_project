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
		change  = false;
        for (int b = 0; b < SET_MAX; b++) {
			cout << "\n\nSET " << (b + 1) << " IN (before): ";
			in[b].dump();
			cout << "\nSET " << (b + 1) << " OUT (before): ";
			out[b].dump();

			// old = in[b]
			Set old(in[b]);

			// out[b] = U in[p] for each successor p of b
			Set unionSet;
			for (int succ = 0; succ < successor[b].size(); succ++) {
				int p;
				successor[b].get(succ, p);
				unite(unionSet, in[p], unionSet);
			}
			swap(out[b], unionSet);

			// in[b] = use[b] U (out[b] - def[b])
			Set dummySet1(use[b]);
			Set dummySet2;
			subtract(out[b], def[b], dummySet2);
			unite(dummySet1, dummySet2, dummySet1);
			swap(in[b], dummySet1);

			// if (in[b] != old)
			//		change = true
			if (!(in[b] == old))
				change = true;

			cout << "\nSET " << (b + 1) << " IN (after): ";
			in[b].dump();
			cout << "\nSET " << (b + 1) << " OUT (after): ";
			out[b].dump();
        }
		cout << "\n==================================";
    } 
	
	cout << endl;
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
