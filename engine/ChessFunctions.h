#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdint>

constexpr int squareIndex(char file, char rank) {
	int f = file - 'a';
	int r = rank - '1';

	return f + r * 8;
}

std::string squareName(int sq);

int countBits(uint64_t b);

void printBoard(const std::array<char, 64>& board);

