#include "bitboard.h"


int rankFiletoSqIndex(int rank, int file) {
	if (rank > 7 || rank < 0 || file > 7 || file < 0) {
		return -1;
	}
	else return rank * 8 + file;
}


Bitboard sqIndextoBB(int sq) {
	return 1ULL << sq; 
}


std::string decToBinary(Bitboard x) {
	if (x == 0) return "0";

	std::string binary = "";
	while (x > 0) {
		binary = (char)('0' + (x & 1)) + binary;
		x >>= 1;
	}

	return binary;
}


bool isInBB(Bitboard& b, int sq) {
	return ((b >> sq) & 1);
}


void fillSq(Bitboard& b, int sq) {
	if (((b >> sq) & 1) == 0) {
		b |= 1ULL << sq;
	}
}

void rmSq(Bitboard& b, int sq) {
	if (((b >> sq) & 1) == 1) {
		b &= ~(1ULL << sq);
	}
}


void printBB(Bitboard& b) {

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

	std::cout << std::format("{:X}", b) << std::endl;
}