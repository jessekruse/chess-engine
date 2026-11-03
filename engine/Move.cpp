#include "Move.h"
#include <iostream>

Move build_move(Move from, Move to, Move Flags) {
	return (from | (to << 6) | (Flags << 12));
}

Move get_from(Move m) {
	return (m & 0x3f);
}

Move get_to(Move m) {
	return (m >> 6) & 0x3f;
}

Move get_flag(Move m) {
	return (m >> 12) & 0x0f;
}

void print_from(Move m) {
	std::cout << "Starting square: " << squareName(get_from(m)) << std::endl;
}

void print_to(Move m) {
	std::cout << "Ending square: " << squareName(get_to(m)) << std::endl;
}

void print_flag(Move m) {
	Move flag = get_flag(m);

	if (flag == QUIET_MOVE) std::cout << "Flag: quiet move" << std::endl;
	if (flag == DOUBLE_PAWN_PUSH) std::cout << "Flag: double pawn push" << std::endl;
	if (flag == KING_CASTLE) std::cout << "Flag: king castle" << std::endl;
	if (flag == QUEEN_CASTLE) std::cout << "Flag: queen castle" << std::endl;
	if (flag == CAPTURE) std::cout << "Flag: capture" << std::endl;
	if (flag == EP_CAPTURE) std::cout << "Flag: en passant capture" << std::endl;
	if (flag == KNIGHT_PROMO) std::cout << "Flag: promote to knight" << std::endl;
	if (flag == BISHOP_PROMO) std::cout << "Flag: promote to bishop" << std::endl;
	if (flag == ROOK_PROMO) std::cout << "Flag: promote to rook" << std::endl;
	if (flag == QUEEN_PROMO) std::cout << "Flag: promote to queen" << std::endl;
	if (flag == KNIGHT_PROMO_CAP) std::cout << "Flag: promote to knight with capture" << std::endl;
	if (flag == BISHOP_PROMO_CAP) std::cout << "Flag: promote to bishop with capture" << std::endl;
	if (flag == ROOK_PROMO_CAP) std::cout << "Flag: promote to rook with capture" << std::endl;
	if (flag == QUEEN_PROMO_CAP) std::cout << "Flag: promote to queen with capture" << std::endl;
}

