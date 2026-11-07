#include "Attacks.h"
#include "Position.h"

std::array<Bitboard, 64> knightAttacks;
std::array<Bitboard, 64> kingAttacks;
std::array<std::array<Bitboard, 64>, 2> pawnAttacks;


// Initialize knight attack table
// masks[3-i] uses the symmetry that backward shifts need to have mirror image masks

static void init_knight_attacks() {

	std::array<int, 4> jumps = { 17, 10, 6, 15};
	std::array<Bitboard, 4> masks = { ~FILE_A, ~(FILE_A | FILE_B), ~(FILE_H | FILE_G), ~FILE_H };

	for (int s = 0; s < 64; ++s) {

		Bitboard b = sqIndextoBB(s);

		for (int i = 0; i < 4; ++i) {
			knightAttacks[s] |= (b << jumps[i]) & masks[i];
			knightAttacks[s] |= (b >> jumps[i]) & masks[3 - i]; 
		}
	}
}


// Initialize king attack table

static void init_king_attacks() {
	std::array<int, 4> jumps = { 1, 7, 8, 9 };
	std::array<Bitboard, 4> pos_masks = { ~FILE_A, ~FILE_H, ~Bitboard{0}, ~FILE_A};
	std::array<Bitboard, 4> neg_masks = { ~FILE_H, ~FILE_A, ~Bitboard{0}, ~FILE_H};

	for (int s = 0; s < 64; ++s) {

		Bitboard b = sqIndextoBB(s);

		for (int i = 0; i < 4; ++i) {
			kingAttacks[s] |= (b << jumps[i]) & pos_masks[i];
			kingAttacks[s] |= (b >> jumps[i]) & neg_masks[i];
		}
	}
}


// Initialize pawn attack table
// masks[1-i] uses the symmetry that backward shifts need to have mirror image masks

static void init_pawn_attacks() {
	std::array<int, 2> jumps = { 7, 9 };
	std::array<Bitboard, 2> masks = { ~FILE_H, ~FILE_A };

	for (int s = 0; s < 64; ++s) {
		Bitboard b = sqIndextoBB(s);

		for (int i = 0; i < 2;++i) {
			pawnAttacks[WHITE][s] |= (b << jumps[i]) & masks[i];
			pawnAttacks[BLACK][s] |= (b >> jumps[i]) & masks[1 - i];
		}
	}
}

void init_attack_tables() {

	init_knight_attacks();
	init_king_attacks();
	init_pawn_attacks();
}

Bitboard rookAttacks(int sq, Bitboard occupied) {

	Bitboard b = sqIndextoBB(sq); 

	std::array<int, 2> RF = sqIndextoRankFile(sq);
	int r_start = RF[0];
	int f_start = RF[1];

	// Fill north ray
	for (int i = 1; i < 8; ++i) {

		// Walk north
		int r_new = r_start + i;

		// Check if off board
		if (r_new >= 8) break;

		// Compute new square index
		int sq_new = rankFiletoSqIndex(r_new, f_start);

		// Fill bitboard
		fillSq(b, sq_new);

		// End walk if occupied by a piece
		if (isInBB(occupied, sq_new)) break;
	}

	// Fill south ray
	for (int i = 1; i < 8; ++i) {

		// Walk south
		int r_new = r_start - i;

		// Check if off board
		if (r_new < 0) break;

		// Compute new square index
		int sq_new = rankFiletoSqIndex(r_new, f_start);

		// Fill bitboard
		fillSq(b, sq_new);

		// End walk if occupied by a piece
		if (isInBB(occupied, sq_new)) break;
	}

	// Fill east ray
	for (int i = 1; i < 8; ++i) {

		// Walk east
		int f_new = f_start + i;

		// Check if off board
		if (f_new >= 8) break;

		// Compute new square index
		int sq_new = rankFiletoSqIndex(r_start, f_new);

		// Fill bitboard
		fillSq(b, sq_new);

		// End walk if occupied by a piece
		if (isInBB(occupied, sq_new)) break;
	}

	// Fill west ray
	for (int i = 1; i < 8; ++i) {

		// Walk west
		int f_new = f_start - i;

		// Check if off board
		if (f_new < 0) break;

		// Compute new square index
		int sq_new = rankFiletoSqIndex(r_start, f_new);

		// Fill bitboard
		fillSq(b, sq_new);

		// End walk if occupied by a piece
		if (isInBB(occupied, sq_new)) break;
	}

	return b;
}

Bitboard bishopAttacks(int sq, Bitboard occupied) {
	Bitboard b = sqIndextoBB(sq);

	std::array<int, 2> RF = sqIndextoRankFile(sq);
	int r_start = RF[0];
	int f_start = RF[1];

	// Fill north east ray
	for (int i = 1; i < 8; ++i) {

		// Walk north east
		int r_new = r_start + i;
		int f_new = f_start + i;

		// Check if off board
		if ((r_new >= 8) || (r_new < 0) || (f_new >= 8) || (f_new < 0)) break;

		// Compute new square index
		int sq_new = rankFiletoSqIndex(r_new, f_new);

		// Fill bitboard
		fillSq(b, sq_new);

		// End walk if occupied by a piece
		if (isInBB(occupied, sq_new)) break;
	}

	// Fill north west ray
	for (int i = 1; i < 8; ++i) {

		// Walk north west 
		int r_new = r_start + i;
		int f_new = f_start - i;

		// Check if off board
		if ((r_new >= 8) || (r_new < 0) || (f_new >= 8) || (f_new < 0)) break;

		// Compute new square index
		int sq_new = rankFiletoSqIndex(r_new, f_new);

		// Fill bitboard
		fillSq(b, sq_new);

		// End walk if occupied by a piece
		if (isInBB(occupied, sq_new)) break;
	}

	// Fill south east ray
	for (int i = 1; i < 8; ++i) {

		// Walk south east
		int r_new = r_start - i;
		int f_new = f_start + i;

		// Check if off board
		if ((r_new >= 8) || (r_new < 0) || (f_new >= 8) || (f_new < 0)) break;

		// Compute new square index
		int sq_new = rankFiletoSqIndex(r_new, f_new);

		// Fill bitboard
		fillSq(b, sq_new);

		// End walk if occupied by a piece
		if (isInBB(occupied, sq_new)) break;
	}

	// Fill south west ray
	for (int i = 1; i < 8; ++i) {

		// Walk north east
		int r_new = r_start - i;
		int f_new = f_start - i;

		// Check if off board
		if ((r_new >= 8) || (r_new < 0) || (f_new >= 8) || (f_new < 0)) break;

		// Compute new square index
		int sq_new = rankFiletoSqIndex(r_new, f_new);

		// Fill bitboard
		fillSq(b, sq_new);

		// End walk if occupied by a piece
		if (isInBB(occupied, sq_new)) break;
	}

	return b;
}

Bitboard queenAttacks(int sq, Bitboard occupied) {
	return rookAttacks(sq, occupied) | bishopAttacks(sq, occupied);
}