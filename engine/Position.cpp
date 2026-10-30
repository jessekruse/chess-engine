#pragma once
#include "Position.h"

// Loads a FEN string into the pieces Bitboards
void Position::loadFEN(FEN f) {
	int square = 56;	// Starting square is a file rank 8 = square 56
	std::string lookup = "PRNBQKprnbqk"; // lookup table to find index matching piece number for pieces array 
	int piece = 0;

	for (auto i = f.begin(); i != f.end(); ++i) {

		// If it is a digit, square jumps that many spaces forward
		if (std::isdigit(*i)) {
			square += *i - '0'; 
		}

		// If it is a '/' then set the index to the a file on the previous rank
		if (*i == '/') {
			square -= 16; 
		}

		// fill the square in the appropriate piece Bitboard
		if (std::isalpha(*i)) {
			piece = lookup.find(*i);
			fillSq(pieces[piece], square); 
			square++;
		}

		// When there is a space, end loading
		if (*i == ' ') break; 

	}
}

// Prints the chess board
void Position::print() {

	std::string lookup = "PRNBQKprnbqk";
	int piece = 0;

	std::array<char, 64> board{};
	board.fill(' ');

	for (auto p = lookup.begin(); p != lookup.end(); ++p) {
		piece = lookup.find(*p);

		for (int i = 0; i < 64; i++) {
			if (isInBB(pieces[piece], i)) {
				board[i] = *p;
			}
			
		}
	}

	printBoard(board);
}

void Position::printFEN() {
	std::cout << fen << std::endl;
}