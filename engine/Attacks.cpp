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

static Bitboard rayWalk(int sq, Bitboard occupied, int r_delta, int f_delta) {
	Bitboard b = 0;

	std::array<int, 2> RF = sqIndextoRankFile(sq);
	int r_start = RF[0];
	int f_start = RF[1];

	for (int i = 1; i < 8; ++i) {

		// Walk in ray direction
		int r_new = r_start + i * r_delta;
		int f_new = f_start + i * f_delta;

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

Bitboard rookAttacks(int sq, Bitboard occupied) {
	
	Bitboard b = 0;

	// Walk north
	b |= rayWalk(sq, occupied, 1, 0);

	// Walk south
	b |= rayWalk(sq, occupied, -1, 0);

	// Walk east
	b |= rayWalk(sq, occupied, 0, 1);

	// Walk west
	b |= rayWalk(sq, occupied, 0, -1);

	return b;
}

Bitboard bishopAttacks(int sq, Bitboard occupied) {
	Bitboard b = 0;

	// Walk north east
	b |= rayWalk(sq, occupied, 1, 1);

	// Walk north west
	b |= rayWalk(sq, occupied, 1, -1);

	// Walk south east
	b |= rayWalk(sq, occupied, -1, 1);

	// Walk south west
	b |= rayWalk(sq, occupied, -1, -1);

	return b;
}

Bitboard queenAttacks(int sq, Bitboard occupied) {
	return rookAttacks(sq, occupied) | bishopAttacks(sq, occupied);
}