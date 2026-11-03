#pragma once
#include <cstdint>

using Move = uint16_t;

inline constexpr Move quiet_move = 0;
inline constexpr Move double_pawn_push = 0b0001;
inline constexpr Move king_castle = 0b0010;
inline constexpr Move queen_castle = 0b0011;
inline constexpr Move captures = 0b0100;
inline constexpr Move ep_capture = 0b0101;
inline constexpr Move knight_promo = 0b1000;
inline constexpr Move bishop_promo = 0b1001;
inline constexpr Move rook_promo = 0b1010;
inline constexpr Move queen_promo = 0b1011;
inline constexpr Move knight_promo_cap = 0b1100;
inline constexpr Move bishop_promo_cap = 0b1101;
inline constexpr Move rook_promo_cap = 0b1110;
inline constexpr Move queen_promo_cap = 0b1111;


Move build_move(Move from, Move to, Move Flags);
Move get_from(Move m);
Move get_to(Move m);
Move get_flags(Move m);
