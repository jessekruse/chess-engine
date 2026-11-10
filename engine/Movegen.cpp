#include "Movegen.h"
#include <iostream>
#include <array>

static void genPieceMoves(int piece_type, const Position& p, MoveList& move_list) {
	Color c = p.sideToMove;

	Bitboard our_side = p.pieces[allWhite + c];
	Bitboard their_side = p.pieces[allBlack - c];
	Bitboard occupied = p.pieces[allPieces];
	
	Bitboard piece = p.pieces[piece_type];
	Bitboard attack_set = 0;

	while (piece) {

		// Get from square for each occupied piece
		int from = pop_lsb(piece);

		// Determine which attack set to use

		if (piece_type == wRook || piece_type == bRook) {
			attack_set = rookAttacks(from, occupied);
		}
		else if (piece_type == wKnight || piece_type == bKnight) {
			attack_set = knightAttacks[from];
		}
		else if (piece_type == wBishop || piece_type == bBishop) {
			attack_set = bishopAttacks(from, occupied);
		}
		else if (piece_type == wQueen || piece_type == bQueen) {
			attack_set = queenAttacks(from, occupied);
		}
		else if (piece_type == wKing || piece_type == bKing) {
			attack_set = kingAttacks[from];
		}

		// Get targets from the attack set
		Bitboard targets = attack_set & ~our_side;

		while (targets) {
			int to = pop_lsb(targets);
			int flag = isInBB(their_side, to) ? CAPTURE : QUIET_MOVE;
			move_list.add(Move(from, to, flag));
		}
	}
}

void generateMoves(const Position& p, MoveList& move_list) {

	// Determine side to move
	Color c = p.sideToMove;
	
	genPieceMoves(wKnight + c * 6, p, move_list);
	genPieceMoves(wKing + c * 6, p, move_list);
	genPieceMoves(wRook + c * 6, p, move_list);
	genPieceMoves(wBishop + c * 6, p, move_list);
	genPieceMoves(wQueen + c * 6, p, move_list);


}