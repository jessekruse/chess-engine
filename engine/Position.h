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

inline constexpr int K = 0b0001;
inline constexpr int Q = 0b0010;
inline constexpr int k = 0b0100;
inline constexpr int q = 0b1000;

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
