#pragma once
#include <cstdint>
#include "ChessFunctions.h"

using Move = uint16_t;

inline constexpr Move QUIET_MOVE = 0;
inline constexpr Move DOUBLE_PAWN_PUSH = 0b0001;
inline constexpr Move KING_CASTLE = 0b0010;
inline constexpr Move QUEEN_CASTLE = 0b0011;
inline constexpr Move CAPTURE = 0b0100;
inline constexpr Move EP_CAPTURE = 0b0101;
inline constexpr Move KNIGHT_PROMO = 0b1000;
inline constexpr Move BISHOP_PROMO = 0b1001;
inline constexpr Move ROOK_PROMO = 0b1010;
inline constexpr Move QUEEN_PROMO = 0b1011;
inline constexpr Move KNIGHT_PROMO_CAP = 0b1100;
inline constexpr Move BISHOP_PROMO_CAP = 0b1101;
inline constexpr Move ROOK_PROMO_CAP = 0b1110;
inline constexpr Move QUEEN_PROMO_CAP = 0b1111;


Move build_move(Move from, Move to, Move Flags);
Move get_from(Move m);
Move get_to(Move m);
Move get_flag(Move m);
void print_from(Move m);
void print_to(Move m);
void print_flag(Move m);

inline constexpr Move CAP_BIT = 0x4000; 
inline constexpr Move PROMO_BIT = 0x8000;

inline bool isCapture(Move m) { return m & CAP_BIT; };
inline bool isPromotion(Move m) { return m & PROMO_BIT; };

