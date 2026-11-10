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
#include "Movegen.h"

using namespace std;

int main() {
	init_attack_tables();

	FEN fStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

	Position p;
	fillSq(p.pieces[bKing],squareIndex('a','1'));
	p.sideToMove = BLACK;
	MoveList ml;

	p.print();

	cout << ml.get_count() << endl;

	generateMoves(p, ml);

	cout << ml.get_count() << endl;

	for (int i = 0; i < ml.count; ++i) {
		ml.list[i].print_move();
	}

	run_tests();
}
