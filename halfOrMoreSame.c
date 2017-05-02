#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct account {};
typedef struct account *Card;


Card getMajorityCard(Card *cards, int size) {
	if (size == 1) {
		return cards[0];
	}

	int split = size / 2;
	Card mostInFirst = getMajorityCard(cards, split);
	Card mostInSecond = getMajorityCard(cards + split, size - split);

	int numFirstOccurences = 0;
	int numSecondOccurences = 0;
	for (int i = 0; i < size; i++) {
		if (cards[i] == mostInFirst) {
			numFirstOccurences++;
		} else if (cards[i] == mostInSecond) {
			numSecondOccurences++;
		}
	}

	if (numFirstOccurences > split) {
		return mostInFirst;
	} else if (numSecondOccurences > split) {
		return mostInSecond;
	} else {
		return NULL;
	}
}

bool halfOrMoreSame(Card *cards, int size) {
	return getMajorityCard(cards, size) != NULL;
}

void testProgram(int seed) {
	// Seed random num generator
	srand(seed);

	// Construct the accounts
	int n = 40;
	Card *cards = malloc(sizeof(*cards) * n);
	cards[0] = malloc(sizeof(struct account));

	for (int i = 1; i < n; i++) {
		if (rand() > RAND_MAX / 2) {
			cards[i] = cards[0];
		} else {
			cards[i] = malloc(sizeof(struct account));
		}
	}

	Card temp = cards[0];
	int indexToSwap = rand() % 40;
	cards[0] = cards[indexToSwap];
	cards[indexToSwap] = temp;
	bool areHalfSame = halfOrMoreSame(cards, n);

	int count = 0;
	for (int i = 0; i < n; i++)
		if (cards[i] == cards[indexToSwap]) count++;

	if ((count >= 20 && areHalfSame) || (count < 20 && !areHalfSame)) {
		printf("Testing with seed %d... algorithm appears correct!\n", seed);
	} else {
		printf("ERROR: Your algorithm appears to reach wrong answer on seed %d.\n", seed);
		exit(1);
	}
}

int main() {
	testProgram(1);
	testProgram(2);
	testProgram(3);
	testProgram(12345);
}
