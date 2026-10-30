#pragma once
#include <cstdint>
#include "Bitboard.h"
#include "ChessFunctions.h"
#include <array>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>

using FEN = std::string;

enum class Color { white, black };

enum Piece {
	wPawn,
	wRook,
	wKnight,
	wBishop,
	wQueen,
	wKing,
	bPawn,
	bRook,
	bKnight,
	bBishop,
	bQueen,
	bKing,
	PieceCount,
};

struct Position {
	std::array<Bitboard, PieceCount> pieces{};
	Color sideToMove = Color::white;
	std::uint8_t canCastle = 0;
	Bitboard enPassant = 0;
	int halfmove = 0;
	int fullmove = 1;
	void loadFEN(const FEN& f);
	void print() const;
	void printFEN() const;
};
