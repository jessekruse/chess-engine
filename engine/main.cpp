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
	
	Move from = squareIndex('e', '2');
	Move to = squareIndex('e', '4');
	Move flag = double_pawn_push;

	Move full_move = build_move(from, to, flag);

	cout << format("{:#x}\n", full_move) << endl;

}
