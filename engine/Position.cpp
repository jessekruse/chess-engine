#include "Position.h"
#include <iostream>

// Loads a FEN string into the pieces Bitboards
void Position::loadFEN(const FEN& f) {

	// Clear all pieces first
	pieces.fill(0);

	int square = 56;	// Starting square is a file rank 8 = square 56
	int piece = 0;

	// Break FEN into its 6 fields
	std::stringstream ss(f);
	std::string token;
	std::vector<std::string> fen_parts{};
	while (std::getline(ss, token, ' ')) {
		fen_parts.push_back(token);
	}

	// Set pieces in bitboards
	for (auto i = fen_parts[0].begin(); i != fen_parts[0].end(); ++i) {

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
	}

	// Set combined pieces bitboards
	for (int p = 0;p < 6;++p) {
		pieces[allWhite] |= pieces[p];
		pieces[allBlack] |= pieces[p + 6];
	}
	pieces[allPieces] = pieces[allWhite] | pieces[allBlack];


	// Set side to move 
	sideToMove = (fen_parts[1][0] == 'w') ? WHITE : BLACK;


	// Set castling rights
	for (auto i = fen_parts[2].begin(); i != fen_parts[2].end(); ++i) {
		if (*i == '-') {
			canCastle = 0;
		}
		if (*i == 'K') {
			canCastle |= K;
		}
		if (*i == 'Q') {
			canCastle |= Q;
		}
		if (*i == 'k') {
			canCastle |= k;
		}
		if (*i == 'q') {
			canCastle |= q;
		}
	}


	// Set en passant
	char file{};
	char rank{};

	for (auto i = fen_parts[3].begin(); i != fen_parts[3].end(); ++i) {
		if (*i == '-') {
			enPassant = 0;
		}
		if (std::isalpha(*i)) {
			file = *i;
		}
		if (std::isdigit(*i)) {
			rank = *i;
		}
	}
	if (fen_parts[3][0] != '-') fillSq(enPassant, squareIndex(file, rank));


	// Set halfmove count
	int ones_place = 0;
	int tens_place = 0;
	int hundreds_place = 0;
	
	if (fen_parts[4].length() == 3) {
		hundreds_place = fen_parts[4][0] - '0';
		tens_place = fen_parts[4][1] - '0';
		ones_place = fen_parts[4][2] - '0';
	}
	if (fen_parts[4].length() == 2) {
		tens_place = fen_parts[4][0] - '0';
		ones_place = fen_parts[4][1] - '0';
	}
	if (fen_parts[4].length() == 1) {
		ones_place = fen_parts[4][0] - '0';
	}

	halfmove = hundreds_place * 100 + tens_place * 10 + ones_place;


	// Set fullmove count
	hundreds_place = 0;
	tens_place = 0;
	ones_place = 0;

	if (fen_parts[5].length() == 3) {
		hundreds_place = fen_parts[5][0] - '0';
		tens_place = fen_parts[5][1] - '0';
		ones_place = fen_parts[5][2] - '0';
	}
	if (fen_parts[5].length() == 2) {
		tens_place = fen_parts[5][0] - '0';
		ones_place = fen_parts[5][1] - '0';
	}
	if (fen_parts[5].length() == 1) {
		ones_place = fen_parts[5][0] - '0';
	}

	fullmove = hundreds_place * 100 + tens_place * 10 + ones_place;

}

// Prints the chess board state
void Position::print() const {

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

	// Print board and pieces
	printBoard(board);

	// Print side to move
	std::cout << "\nSide to Move: " << ((sideToMove == WHITE) ? "White" : "Black") << std::endl;

	// Print castling rights
	std::string rights{};
	if ((canCastle & K) != 0) rights.push_back('K');
	if ((canCastle & Q) != 0) rights.push_back('Q');
	if ((canCastle & k) != 0) rights.push_back('k');
	if ((canCastle & q) != 0) rights.push_back('q');
	if (canCastle == 0) rights.push_back('-');

	std::cout << "Castling Rights: " << rights << std::endl;

	// Print En Passant squares
	if (enPassant == 0) {
		std::cout << "No En Passant" << std::endl;
	}
	else {
		std::cout << "En Passant: " << squareName(lsb(enPassant)) << std::endl;
	}

	// Print half move count
	std::cout << "Half Move: " << halfmove << std::endl;

	// Print full move count
	std::cout << "Full Move: " << fullmove << std::endl;
}



FEN Position::getFEN() const {

	// Generate character array for pieces
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

	std::string fen{};

	// Create piece field of FEN
	int count = 0;

	for (int r = 7; r >= 0; --r) {
		for (int f = 0; f <= 8;++f) {

			// Check if end of the rank
			if (f == 8) {
				// Check if there were empty squares before end of rank
				if (count != 0) {
					fen.push_back('0' + count);
					count = 0;
				}
				// Make sure it isn't the last rank
				if (r > 0) fen.push_back('/');
				continue;
			}

			int sq = r * 8 + f;

			// Check if board square is empty and increment count
			if (board[sq] == ' ') {
				count++;
			}

			// Check piece on square
			if (board[sq] != ' ') {
				if (count !=0) fen.push_back('0' + count);
				count = 0;
				fen.push_back(board[sq]);
			}
		}
	}

	// Add side to move to FEN
	fen.push_back(' ');
	if (sideToMove == Color::WHITE) {
		fen.push_back('w');
	}
	else fen.push_back('b');


	// Add castling rights to FEN
	fen.push_back(' ');
	std::array<int, 4> cChecks = { K, Q, k, q };
	std::array<char, 4> cChars = { 'K','Q','k','q' };

	for (int i = 0; i < 4; ++i) {
		if ((canCastle & cChecks[i]) != 0) {
			fen.push_back(cChars[i]);
		}
	}
	if (canCastle == 0) fen.push_back('-');

	// Add en passant to FEN
	fen.push_back(' ');

	if (enPassant) {
		int sq = lsb(enPassant);
		fen.push_back('a' + sq % 8);
		fen.push_back('1' + sq / 8);
	}
	else {
		fen.push_back('-');
	}

	// Add half move count to FEN
	fen.push_back(' ');
	fen += std::to_string(halfmove);

	// Add full move count to FEN;
	fen.push_back(' ');
	fen += std::to_string(fullmove);

	return fen;

}