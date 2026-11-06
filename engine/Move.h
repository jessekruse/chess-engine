#pragma once
#include <cstdint>
#include "ChessFunctions.h"

using move_t = uint16_t;

inline constexpr move_t QUIET_MOVE = 0;
inline constexpr move_t DOUBLE_PAWN_PUSH = 0b0001;
inline constexpr move_t KING_CASTLE = 0b0010;
inline constexpr move_t QUEEN_CASTLE = 0b0011;
inline constexpr move_t CAPTURE = 0b0100;
inline constexpr move_t EP_CAPTURE = 0b0101;
inline constexpr move_t KNIGHT_PROMO = 0b1000;
inline constexpr move_t BISHOP_PROMO = 0b1001;
inline constexpr move_t ROOK_PROMO = 0b1010;
inline constexpr move_t QUEEN_PROMO = 0b1011;
inline constexpr move_t KNIGHT_PROMO_CAP = 0b1100;
inline constexpr move_t BISHOP_PROMO_CAP = 0b1101;
inline constexpr move_t ROOK_PROMO_CAP = 0b1110;
inline constexpr move_t QUEEN_PROMO_CAP = 0b1111;

inline constexpr move_t CAP_BIT = 0x4000;
inline constexpr move_t PROMO_BIT = 0x8000;

struct Move {
	move_t m;

	// Default constructor
	Move() {
		m = 0;
	}
	// Parameterized constructor
	Move(move_t from, move_t to, move_t flag) : m(from | (to << 6) | (flag << 12)) {}

	move_t get_from() const { return (m & 0x3f); };
	move_t get_to() const { return (m >> 6) & 0x3f; };
	move_t get_flag() const { return (m >> 12) & 0x0f; };

	void print_from() const;
	void print_to() const;
	void print_flag() const;

	bool isCapture() const { return m & CAP_BIT; };
	bool isPromotion() const { return m & PROMO_BIT; };
};

