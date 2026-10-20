#pragma once
#include <iostream>
#include <string>
#include <format>

using Bitboard = std::uint64_t;

int rankFiletoSqIndex(int rank, int file);

Bitboard sqIndextoBB(int sq);

std::string decToBinary(Bitboard x);

bool isInBB(Bitboard& b, int sq);

void fillSq(Bitboard& b, int sq);

void rmSq(Bitboard& b, int sq);

void printBB(Bitboard& b);