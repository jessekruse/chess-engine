#include "Position.h"
#include <iostream>
#include <cassert>
#include "Attacks.h"

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
	halfmove = std::stoi(fen_parts[4]);

	// Set fullmove count
	fullmove = std::stoi(fen_parts[5]);

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


Piece Position::pieceOn(int sq) const {
	Color c = (isInBB(pieces[allWhite], sq)) ? WHITE : BLACK;

	// Search through the piece bitboards for the color
	for (int i = 0; i < 6;++i) {
		if (isInBB(pieces[i + c * 6], sq)) return (Piece)(i + c * 6);
	}

	// If square is empty return PieceCount as a flag
	return PieceCount;
}

Color colorOf(Piece p) {
	assert(p >= 0 && p < 12);
	return (p < 6) ? WHITE : BLACK;
}

// Lookup for promotion piece
static constexpr std::array<Piece, 8> promoPiece = {
	wKnight, wBishop, wRook, wQueen,
	bKnight, bBishop, bRook, bQueen };

// Castling masks
static constexpr std::array<uint8_t, 64> buildCastleMasks() {
	std::array<uint8_t, 64> castleMask{};
	castleMask.fill(0b1111);

	int a1 = squareIndex('a', '1');
	int e1 = squareIndex('e', '1');
	int h1 = squareIndex('h', '1');
	int a8 = squareIndex('a', '8');
	int e8 = squareIndex('e', '8');
	int h8 = squareIndex('h', '8');

	castleMask[a1] = ~Q;
	castleMask[e1] = (~Q & ~K);
	castleMask[h1] = ~K;
	castleMask[a8] = ~q;
	castleMask[e8] = (~q & ~k);
	castleMask[h8] = ~k;

	return castleMask;
}

static constexpr std::array<uint8_t, 64> castleMask = buildCastleMasks();

// Build table for rook moves for castling
struct CR {
	int h1 = squareIndex('h', '1');
	int f1 = squareIndex('f', '1');
	int a1 = squareIndex('a', '1');
	int d1 = squareIndex('d', '1');
	int h8 = squareIndex('h', '8');
	int f8 = squareIndex('f', '8');
	int a8 = squareIndex('a', '8');
	int d8 = squareIndex('d', '8');

	std::array<int, 4> from = { h1, a1, h8, a8 };
	std::array<int, 4> to = { f1, d1, f8, d8 };
};

static constexpr CR castleRook;

bool Position::makeMove(Move m) {

	int from = m.get_from();	// Get from square
	int to = m.get_to();		// Get to square
	int flag = m.get_flag();	// Get the move flag

	Bitboard fromBB = sqIndextoBB(from);	// Create a bitboard for the from square
	Bitboard toBB = sqIndextoBB(to);		// Create a bitboard for the to square
	Bitboard fromToBB = fromBB | toBB;		// Create a bitboard with both from and to squares

	Piece fromPiece = pieceOn(from);	// Get the piecetype that is moving
	assert(fromPiece != PieceCount);	// Make sure we actually have a piece

	// If move is a capture, remove captured piece
	if (m.isCapture()) {
		int captureSq = to;

		// Check for en passant to update the capture square
		if (flag == EP_CAPTURE) {
			captureSq = (colorOf(fromPiece) == WHITE) ? to - 8 : to + 8;
		}

		Bitboard captureBB = sqIndextoBB(captureSq);

		// Get the captured piece type
		Piece capturePiece = pieceOn(captureSq);
		assert(capturePiece != PieceCount);
		assert(colorOf(capturePiece) != colorOf(fromPiece));

		// Remove captured piece
		pieces[capturePiece] ^= captureBB;
		pieces[allWhite + opposite(sideToMove)] ^= captureBB;
	}

	// Remove castling rights if necessary
	canCastle &= (castleMask[from] & castleMask[to]);

	// Move rooks for castling
	if (flag == KING_CASTLE || flag == QUEEN_CASTLE) {
		int index = (flag & 0b0001) + sideToMove*2;
		
		Bitboard rookFromTo = sqIndextoBB(castleRook.from[index]) | sqIndextoBB(castleRook.to[index]);

		pieces[wRook + 6 * sideToMove] ^= rookFromTo;
		pieces[allWhite + sideToMove] ^= rookFromTo;
	}

	// Move the from piece
	pieces[fromPiece] ^= fromToBB;
	pieces[allWhite + sideToMove] ^= fromToBB;

	
	// Check for promotion
	if (m.isPromotion()) {
		// Remove pawn
		pieces[fromPiece] ^= toBB;

		// Get the promotion piece
		int promoFlag = flag & 0b0011; 
		Piece toPiece = promoPiece[promoFlag + colorOf(fromPiece) * 4];

		// Place promotion piece where pawn was
		pieces[toPiece] ^= toBB;
	}

	// Update allPieces bitboard
	pieces[allPieces] = pieces[allWhite] | pieces[allBlack];

	// Check if king is under attack after move
	int kingSq = lsb(pieces[wKing + 6 * sideToMove]);
	if (isSquareAttacked(kingSq, opposite(sideToMove))) return false;

	// Set or reset en passant
	if (flag == DOUBLE_PAWN_PUSH) {
		enPassant = (colorOf(fromPiece) == WHITE) ? sS(toBB) : sN(toBB);
	}
	else enPassant = 0;
	

	// Check if half move count resets
	if (fromPiece == wPawn || fromPiece == bPawn || m.isCapture()) {
		halfmove = 0;
	}
	else halfmove++;

	// If black moves then full move increments
	if (sideToMove == BLACK) fullmove++;

	// Switch side to move
	sideToMove = (sideToMove == WHITE) ? BLACK : WHITE;

	return true;
}

bool Position::isSquareAttacked(int sq, Color enemyC) const {
	/*
		We have the king square and the color of the king from sideToMove
		I need to generate attacks for each of the pieces from that square and 
		see if they intersect with the same enemy piece types.
	*/

	Bitboard occupied = pieces[allPieces];

	// Get enemy piece bitboards
	Bitboard pawns = pieces[wPawn + 6 * enemyC];
	Bitboard rooks = pieces[wRook + 6 * enemyC];
	Bitboard knights = pieces[wKnight + 6 * enemyC];
	Bitboard bishops = pieces[wBishop + 6 * enemyC];
	Bitboard queens = pieces[wQueen + 6 * enemyC];
	Bitboard king = pieces[wKing + 6 * enemyC];

	// Check if there are enemy pieces attacking that square
	if ((pawnAttacks[opposite(enemyC)][sq] & pawns) != 0) return true;
	if ((rookAttacks(sq, occupied) & (queens | rooks)) != 0) return true;
	if ((knightAttacks[sq] & knights) != 0) return true;
	if ((bishopAttacks(sq, occupied) & (queens | bishops)) != 0) return true;
	if ((kingAttacks[sq] & king) != 0) return true;
}