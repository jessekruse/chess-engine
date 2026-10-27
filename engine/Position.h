#pragma once

#include <iostream>
#include <cstdint>
#include "Bitboard.h"
#include "ChessFunctions.h"
#include <array>
#include <string>

using FEN = std::string;

FEN fTest = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";

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
	void loadFEN(FEN fen);
	void print();
	void printFEN();
};
