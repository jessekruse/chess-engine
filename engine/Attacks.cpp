#include "Attacks.h"

std::array<Bitboard, 64> knightAttacks;
std::array<Bitboard, 64> kingAttacks;
std::array<std::array<Bitboard, 64>, 2> pawnAttacks;


// Initialize knight attack table

void init_knight_attacks() {

	std::array<int, 4> jumps = { 17, 10, 6, 15};
	std::array<Bitboard, 4> masks = { ~FILE_A, ~(FILE_A | FILE_B), ~(FILE_H | FILE_G), ~FILE_H };

	for (int s = 0; s < 64; ++s) {

		Bitboard b = sqIndextoBB(s);

		for (int i = 0; i < 4; ++i) {
			knightAttacks[s] |= (b << jumps[i]) & masks[i];
			knightAttacks[s] |= (b >> jumps[i]) & masks[3 - i];
		}
	}

	int count = 0;
	for (int s = 0; s < 64; ++s) {
		count += popcount(knightAttacks[s]);
	}

	std::cout << "knightAttacks popcount: " << count << std::endl;
}


// Initialize king attack table

void init_king_attacks() {
	std::array<int, 4> jumps = { 1, 7, 8, 9 };
	std::array<Bitboard, 4> pos_masks = { ~FILE_A, ~FILE_H, ~0, ~FILE_A };
	std::array<Bitboard, 4> neg_masks = { ~FILE_H, ~FILE_A, ~0, ~FILE_H };

	for (int s = 0; s < 64; ++s) {

		Bitboard b = sqIndextoBB(s);

		for (int i = 0; i < 4; ++i) {
			kingAttacks[s] |= (b << jumps[i]) & pos_masks[i];
			kingAttacks[s] |= (b >> jumps[i]) & neg_masks[i];
		}
	}

	int count = 0;
	for (int s = 0; s < 64; ++s) {
		count += popcount(kingAttacks[s]);
	}

	std::cout << "kingAttacks popcount: " << count << std::endl;
}


// Initialize pawn attack table

void init_pawn_attacks() {
	std::array<int, 2> jumps = { 7, 9 };
	std::array<Bitboard, 2> masks = { ~FILE_H, ~FILE_A };

	for (int s = 0; s < 64; ++s) {
		Bitboard b = sqIndextoBB(s);

		for (int i = 0; i < 2;++i) {
			pawnAttacks[WHITE][s] |= (b << jumps[i]) & masks[i];
			pawnAttacks[BLACK][s] |= (b >> jumps[i]) & masks[1 - i];
		}
	}

	int count = 0;
	for (int s = 0; s < 64; ++s) {
		count += popcount(pawnAttacks[WHITE][s]);
	}

	std::cout << "white pawns popcount: " << count << std::endl;

}

void init_attack_tables() {

	init_knight_attacks();
	init_king_attacks();
	init_pawn_attacks();
}