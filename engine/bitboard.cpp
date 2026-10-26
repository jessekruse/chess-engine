#include "bitboard.h"


// Converts a rank (0-7) and file (0-7) to a square index (0-63)
int rankFiletoSqIndex(int rank, int file) {
	if (rank > 7 || rank < 0 || file > 7 || file < 0) {
		return -1;
	}
	else return rank * 8 + file;
}

// Takes an individual square index and converts it into a Bitboard
// Not particularly useful
Bitboard sqIndextoBB(int sq) {
	return 1ULL << sq; 
}

// Converts a Bitboard number to a binary string to print out
std::string decToBinary(Bitboard x) {
	if (x == 0) return "0";

	std::string binary = "";
	while (x > 0) {
		binary = (char)('0' + (x & 1)) + binary;
		x >>= 1;
	}

	return binary;
}

// Checks if a square (0-63) is occupied in a Bitboard
bool isInBB(Bitboard b, int sq) {
	return ((b >> sq) & 1);
}

// Fills a square in a Bitboard so it is occupied.
void fillSq(Bitboard& b, int sq) {
		b |= 1ULL << sq;
}

// Removes a square in a Bitboard so it is no longer occupied.
void rmSq(Bitboard& b, int sq) {
		b &= ~(1ULL << sq);
}

/*
	Prints a Bitboard on a rank and file grid like a chess board 
	but only with 1's and .'s. 1 represents an occupied square and 
	. represents an empty square.
	Also prints the hex value for that bitboard beneath the grid. 
*/ 
void printBB(Bitboard b) {

	int sq;

	for (int rank = 7; rank >= 0; --rank) {

		std::cout << rank + 1 << " ";

		for (int file = 0; file < 8; ++file) {
			sq = rankFiletoSqIndex(rank, file);
			
			if (isInBB(b, sq)) {
				std::cout << "1 ";
			}
			else {
				std::cout << ". ";
			}
			
		}

		std::cout << std::endl;
	}

	std::cout << "  a b c d e f g h" << std::endl;

	std::cout << "0x" << std::format("{:X}", b) << std::endl;
}


// Counts the number of set bits/occupied squares in a bitboard
int popcount(Bitboard b) {
	return std::popcount(b);
}

// Returns the index for the lowest occupied square (least significant bit)
int lsb(Bitboard b) {
	if (b == 0) {
		return -1;
	}
	else {
		return std::countr_zero(b);
	}
}

// Finds the lsb, removes it, then returns the index of the bit it just removed
int pop_lsb(Bitboard& b) {
	int l = lsb(b);

	b = b & (b - 1);

	return l;
}

Bitboard sN(Bitboard b) {
	return b << 8;
}

Bitboard sE(Bitboard b) {
	return ((b << 1) & ~FILE_A);
}

Bitboard sS(Bitboard b) {
	return b >> 8;
}

Bitboard sW(Bitboard b) {
	return ((b >> 1) & ~FILE_H);
}