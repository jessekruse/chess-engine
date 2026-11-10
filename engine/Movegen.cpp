#include "Movegen.h"
#include <iostream>

void generateMoves(const Position& p, MoveList& move_list) {
	// Determine side to move
	Color us = p.sideToMove;
	Color them = opposite(us);

	Bitboard our_side = p.pieces[allWhite + us];
	Bitboard their_side = p.pieces[allBlack - us];
	Bitboard occupied = p.pieces[allPieces];


	// Get knight pseudo legal moves
	Bitboard knights = p.pieces[wKnight + us * 6];

	while (knights) {

		int from = pop_lsb(knights);
		Bitboard targets = knightAttacks[from] & ~our_side;

		while (targets) {
			int to = pop_lsb(targets);
			int flag = isInBB(their_side, to) ? CAPTURE : QUIET_MOVE;
			move_list.add(Move(from, to, flag));
		}
	}


	// Get king pseudo legal moves
	Bitboard king = p.pieces[wKing + us * 6];

	while (king) {
		int from = pop_lsb(king);
		Bitboard targets = kingAttacks[from] & ~our_side;

		while (targets) {
			int to = pop_lsb(targets);
			int flag = isInBB(their_side, to) ? CAPTURE : QUIET_MOVE;
			move_list.add(Move(from, to, flag));
		}
	}
	

	// Get rook pseudo legal moves

	Bitboard rooks = p.pieces[wRook + 6 * us];
	while (rooks) {
		int from = pop_lsb(rooks);

		Bitboard targets = rookAttacks(from, occupied) & ~our_side;
		while (targets) {
			int to = pop_lsb(targets);
			int flag = isInBB(their_side, to) ? CAPTURE : QUIET_MOVE;
			move_list.add(Move(from, to, flag));
		}
	}

	// Get bishop pseudo legal moves

	Bitboard bishops = p.pieces[wBishop + 6 * us];
	while (bishops) {
		int from = pop_lsb(bishops);

		Bitboard targets = bishopAttacks(from, occupied) & ~our_side;
		while (targets) {
			int to = pop_lsb(targets);
			int flag = isInBB(their_side, to) ? CAPTURE : QUIET_MOVE;
			move_list.add(Move(from,to,flag));
		}
	}

	// Get queen pseudo legal moves

	Bitboard queens = p.pieces[wQueen + 6 * us];
	while (queens) {
		int from = pop_lsb(queens);

		Bitboard targets = queenAttacks(from, occupied) & ~our_side;
		while (targets) {
			int to = pop_lsb(targets);
			int flag = isInBB(their_side, to) ? CAPTURE : QUIET_MOVE;
			move_list.add(Move(from, to, flag));
		}
	}
}