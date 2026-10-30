#include "Position.h"

// Loads a FEN string into the pieces Bitboards
void Position::loadFEN(const FEN& f) {
	int square = 56;	// Starting square is a file rank 8 = square 56
	std::string lookup = "PRNBQKprnbqk"; // lookup table to find index matching piece number for pieces array 
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

	// Set side to move value
	if (fen_parts[1][0] == 'w') {
		sideToMove = Color::white;
	}
	if (fen_parts[1][0] == 'b') {
		sideToMove = Color::black;
	}


	// Set castling rights
	int K = 0b0001;
	int Q = 0b0010;
	int k = 0b0100;
	int q = 0b1000;

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


	// Set move count
	int ones_place = 0;
	int tens_place = 0;
	int hundreds_place = 0;
	
	if (fen_parts[4].length() == 3) {
		hundreds_place = fen_parts[4][0] - '0';
		tens_place = fen_parts[4][0] - '0';
		ones_place = fen_parts[4][1] - '0';
	}
	if (fen_parts[4].length() == 2) {
		tens_place = fen_parts[4][0] - '0';
		ones_place = fen_parts[4][1] - '0';
	}
	else {
		ones_place = fen_parts[4][0] - '0';
	}

	halfmove = hundreds_place * 100 + tens_place * 10 + ones_place;

	// Calculate fullmove
	if (fen_parts[5].length() == 3) {
		hundreds_place = fen_parts[4][0] - '0';
		tens_place = fen_parts[4][0] - '0';
		ones_place = fen_parts[4][1] - '0';
	}
	if (fen_parts[5].length() == 2) {
		tens_place = fen_parts[5][0] - '0';
		ones_place = fen_parts[5][1] - '0';
	}
	else {
		ones_place = fen_parts[5][0] - '0';
	}

	fullmove = hundreds_place * 100 + tens_place * 10 + ones_place;

}

// Prints the chess board
void Position::print() const {

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

	// Print board and pieces
	printBoard(board);

	// Print side to move
	std::cout << "\nSide to Move: " << ((sideToMove == Color::white) ? "White" : "Black") << std::endl;

	// Print castling rights
	std::string rights{};
	if (isInBB(canCastle,0)) rights.push_back('K');
	if (isInBB(canCastle,1)) rights.push_back('Q');
	if (isInBB(canCastle,2)) rights.push_back('k');
	if (isInBB(canCastle,3)) rights.push_back('q');
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

void Position::printFEN() const {
}