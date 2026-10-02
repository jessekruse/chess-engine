#include "ChessFunctions.h"


using namespace std;

int squareIndex(char file, char rank) {
	int f = file - 'a';
	int r = rank - '1';

	return f + r * 8;
}

string squareName(int sq) {
	string sqName;

	int r = sq / 8;
	int f = sq % 8;

	char file = f + 'a';
	char rank = r + '1';

	sqName += file;
	sqName += rank;

	return sqName;
}

int countBits(uint64_t b) {
	int numBits = 0;

	for (int i = 0; i < 64; ++i) {
		if (((b >> i) & 1) == 1) {
			numBits += 1;
		}
	}

	return numBits;

}

void printBoard(const array<char, 64>& board) {

	for (int rank = 7; rank >= 0; --rank) {

		cout << rank + 1 << " ";

		for (int file = 0; file < 8; ++file) {
			cout << board[rank * 8 + file] << ' ';
		}

		cout << endl;
	}

	cout << "  a b c d e f g h" << endl;
}