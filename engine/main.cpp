#include <iostream>
#include <array>
#include "ChessFunctions.h"
#include "Bitboard.h"
#include <cmath>
#include "Tests.h"
#include "Position.h"
#include "Move.h"
#include <format>
#include "Attacks.h"

using namespace std;

int main() {
	init_attack_tables();

	move_t from = squareIndex('e', '2');
	move_t to = squareIndex('e', '4');
	move_t flag = DOUBLE_PAWN_PUSH;

	Move m(from, to, flag);

	MoveList ml;

	cout << ml.count() << endl;

	ml.add(m);
	ml.add(m);

	cout << ml.count() << endl;

	ml.list[0].print_move();

	run_tests();
}
