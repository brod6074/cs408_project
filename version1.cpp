#include <iostream>
using namespace std;

static const int SET_MAX = 6;
static const int EMPTY = 0;

void setInitialize(int set[][SET_MAX], int initVal);
void setUnion(int set1[], int set2[]);
void setDifference(int set1[], int set2[]);
bool isEmptySet(int set[]);

int main() {

	int in[SET_MAX][SET_MAX];
	int out[SET_MAX][SET_MAX];
	int def[SET_MAX][SET_MAX];
	int use[SET_MAX][SET_MAX];
	int successor[SET_MAX][SET_MAX];
	int old[SET_MAX][SET_MAX];

	setInitialize(in, EMPTY);
	setInitialize(out, EMPTY);
	setInitialize(def, EMPTY);
	setInitialize(use, EMPTY);
	setInitialize(successor, EMPTY);
	setInitialize(old, EMPTY);

	bool change = true;
	while (change) {
		change = false;

		for (int i = 0; i < SET_MAX; i++) {
			// OLD = in [B]

			//out[B] =
			// for each successor P of B
			//   U in[P]

			// in[B] = use[B] U (out[B] - def[B])

			// if (in[B] != OLD)
			//		change = true;
		}
	}

	return 0;
}

void setInitialize(int set[][SET_MAX], int initVal) {
	int *baseAddr = &set[0][0];

	for (int i = 0; i < SET_MAX * SET_MAX; i++)
		*(baseAddr + i) = initVal;
}