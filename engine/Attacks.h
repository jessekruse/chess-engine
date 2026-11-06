#pragma once
#include <cstdint>
#include "Bitboard.h"
#include "Move.h"
#include <array>
#include "Position.h"

extern std::array<Bitboard, 64> knightAttacks;
extern std::array<Bitboard, 64> kingAttacks;
extern std::array<std::array<Bitboard, 64>, 2> pawnAttacks;

void init_attack_tables();

void init_knight_attacks();

void init_king_attacks();

void init_pawn_attacks();