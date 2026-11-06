#include "Move.h"
#include <iostream>


void Move::print_from() const {
	std::cout << "Starting square: " << squareName(get_from()) << std::endl;
}

void Move::print_to() const {
	std::cout << "Ending square: " << squareName(get_to()) << std::endl;
}

void Move::print_flag() const {
	move_t flag = get_flag();

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

