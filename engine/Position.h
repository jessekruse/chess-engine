#pragma once
#include <cstdint>
#include "Bitboard.h"
#include "ChessFunctions.h"
#include <array>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <string_view>

using FEN = std::string;

inline constexpr int K = 0b0001;
inline constexpr int Q = 0b0010;
inline constexpr int k = 0b0100;
inline constexpr int q = 0b1000;

inline constexpr std::string_view lookup = "PRNBQKprnbqk";

enum Color { WHITE, BLACK };

inline Color opposite(Color c) { return (Color)(c ^ 1); };

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
	allWhite,
	allBlack,
	allPieces,
	PieceCount,
};

static_assert(bPawn == wPawn + 6);
static_assert(bRook == wRook + 6);
static_assert(bKnight == wKnight + 6);
static_assert(bBishop == wBishop + 6);
static_assert(bQueen == wQueen + 6);
static_assert(bKing == wKing + 6);
static_assert(allBlack == allWhite + 1);

struct Position {
	std::array<Bitboard, PieceCount> pieces{};
	Color sideToMove = WHITE;
	std::uint8_t canCastle = 0;
	Bitboard enPassant = 0;
	int halfmove = 0;
	int fullmove = 1;
	void loadFEN(const FEN& f);
	void print() const;
	FEN getFEN() const;
};

static_assert(sizeof(Position) <= 160);
