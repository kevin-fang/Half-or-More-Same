#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct account {};
typedef struct account *Card;

Card getMostCardAppearances(Card *cards, int size) {
	Card *firstHalf = malloc(sizeof(Card) * size / 2);
	Card *secondHalf = malloc(sizeof(Card) * (size - size / 2));
	memcpy(firstHalf, cards, size / 2);
	memcpy(secondHalf, cards, size - size / 2);
	Card mostInFirst = getMostCardAppearances(firstHalf, size / 2);
	Card mostInSecond = getMostCardAppearances(secondHalf, size - size / 2);

}

bool halfOrMoreSame(Card *cards, int size) {
	Card mostAppeared = getMostCardAppearances(cards, size);
	int numEquals = 0;
	for (int i = 0; i < size; i++) {
		if (cards[i] == mostAppeared) {
			numEquals++;
		}
	}
	if (numEquals >= size / 2) {
		return true;
	}
	return false;
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
	}
}

int main() {
	testProgram(1);
	testProgram(2);
	testProgram(3);
	testProgram(12345);
}
