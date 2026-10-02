#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>

int squareIndex(char file, char rank);

std::string squareName(int sq);

int countBits(uint64_t b);

void printBoard(const std::array<char, 64>& board);