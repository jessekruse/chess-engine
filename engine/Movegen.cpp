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

void genPawnMoves(const Position& p, MoveList& move_list) {

	Color c = p.sideToMove;
	std::array<int, 2> push = { 8,-8 };

	std::array<move_t, 4> promo_flags = { 
		KNIGHT_PROMO, 
		BISHOP_PROMO, 
		ROOK_PROMO, 
		QUEEN_PROMO };
	std::array<move_t, 4> promo_cap_flags = {
		KNIGHT_PROMO_CAP,
		BISHOP_PROMO_CAP,
		ROOK_PROMO_CAP,
		QUEEN_PROMO_CAP
	};

	Bitboard our_side = p.pieces[allWhite + c];
	Bitboard their_side = p.pieces[allBlack - c];
	Bitboard occupied = p.pieces[allPieces];

	Bitboard pawns = p.pieces[wPawn + c * 6];
	
	while (pawns) {
		int from = pop_lsb(pawns);

		// Generate single pawn push moves
		// Check that the next square is not occupied
		if (!isInBB(occupied, from + push[c])) {
			int to = from + push[c];

			// Check if moving to promo square
			if (isInBB(RANK_1 | RANK_8, to)) {
				for (int i = 0; i < 4; i++) {
					int flag = promo_flags[i];
					move_list.add(Move(from, to, flag));
				}
			}
			else {
				int flag = QUIET_MOVE;
				move_list.add(Move(from, to, flag));
			}
		}

		// Generate double pawn push moves
		// Check that pawn is on starting rank
		// Check that the two squares in front are not occupied
		if (isInBB(RANK_2 | RANK_7, from) && !isInBB(occupied, from + push[c]) && !isInBB(occupied, from + 2 * push[c])) {
			int to = from + 2 * push[c];
			int flag = DOUBLE_PAWN_PUSH;
			move_list.add(Move(from, to, flag));
		}

		// Generate possible capture moves
		Bitboard targets = pawnAttacks[c][from] & ~our_side;
		
		while (targets) {
			int to = pop_lsb(targets);

			// Check if target squares are occupied by enemy piece
			if (isInBB(their_side, to)) {

				// Check if the potential capture square is on promo rank
				if (isInBB(RANK_1 | RANK_8, to)) {
					for (int i = 0; i < 4; i++) {
						int flag = promo_cap_flags[i];
						move_list.add(Move(from, to, flag));
					}
				}
				else {
					int flag = CAPTURE;
					move_list.add(Move(from, to, flag));
				}
			}

			// Check if en passant is possible
			if (isInBB(p.enPassant, to)) {
				int flag = EP_CAPTURE;
				move_list.add(Move(from, to, flag));
			}
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
	genPawnMoves(p, move_list);

}