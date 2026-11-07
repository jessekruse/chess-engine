#pragma once
#include <cstdint>
#include "Bitboard.h"
#include <array>

extern std::array<Bitboard, 64> knightAttacks;
extern std::array<Bitboard, 64> kingAttacks;
extern std::array<std::array<Bitboard, 64>, 2> pawnAttacks;

void init_attack_tables();

Bitboard rookAttacks(int sq, Bitboard occupied);

Bitboard bishopAttacks(int sq, Bitboard occupied);

Bitboard queenAttacks(int sq, Bitboard occupied);

Bitboard rayWalk(int sq, Bitboard occupied, int r_delta, int f_delta);