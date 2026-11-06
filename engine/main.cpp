#include <iostream>
#include <array>
#include "ChessFunctions.h"
#include "Bitboard.h"
#include <cmath>
#include "Tests.h"
#include "Position.h"
#include "Move.h"
#include <format>

using namespace std;

int main() {
	
	Move from = squareIndex('e', '5');
	Move to = squareIndex('d', '6');
	Move flag = EP_CAPTURE;

	Move full_move = build_move(from, to, flag);

	cout << format("{:#x}\n", full_move) << endl;

	print_from(full_move);
	print_to(full_move);
	print_flag(full_move);

}
