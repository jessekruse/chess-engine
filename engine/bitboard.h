#pragma once
#include <iostream>
#include <string>
#include <format>
#include <bit>

using Bitboard = std::uint64_t;

inline constexpr Bitboard RANK_1{ 0xFF };
inline constexpr Bitboard RANK_2{ RANK_1 << 8 };
inline constexpr Bitboard RANK_7{ RANK_1 << 48 };
inline constexpr Bitboard RANK_8{ RANK_1 << 56 }; 
inline constexpr Bitboard FILE_A{ 0x101010101010101 };
inline constexpr Bitboard FILE_B{ 0x202020202020202 };
inline constexpr Bitboard FILE_G{ 0x4040404040404040 };
inline constexpr Bitboard FILE_H{ 0x8080808080808080 };

int rankFiletoSqIndex(int rank, int file);

Bitboard sqIndextoBB(int sq);

std::string decToBinary(Bitboard x);

bool isInBB(Bitboard& b, int sq);

void fillSq(Bitboard& b, int sq);

void rmSq(Bitboard& b, int sq);

void printBB(Bitboard& b);

int popcount(Bitboard& b);

int lsb(Bitboard& b);

int pop_lsb(Bitboard& b);

Bitboard sN(Bitboard& b);

Bitboard sE(Bitboard& b);

Bitboard sS(Bitboard& b);

Bitboard sW(Bitboard& b);