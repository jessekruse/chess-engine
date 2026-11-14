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

	FEN fKiwipete = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
	FEN fFullMove = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
	FEN fCastle = "r3k2r/8/8/8/8/8/8/R3K2R b KQ - 0 1";
	FEN fStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

	Move m;
	m.update("e4", "d5", CAPTURE);

	Position p;
	p.loadFEN("8/P7/8/8/8/8/8/k6K w - - 0 1");

	cout << p.getFEN() << endl;
	m.update("a7", "a8", ROOK_PROMO);
	p.makeMove(m);
	cout << p.getFEN() << endl;

	cout << endl;

	p.loadFEN("k7/8/8/8/8/8/1p6/R6K b - - 3 40");
	cout << p.getFEN() << endl;
	m.update("b2", "a1", BISHOP_PROMO_CAP);
	p.makeMove(m);
	cout << p.getFEN() << endl;

	cout << endl;

	p.loadFEN("r3k3/1P6/8/8/8/8/8/4K3 w - - 0 1");
	cout << p.getFEN() << endl;
	m.update("b7", "a8", QUEEN_PROMO_CAP);
	p.makeMove(m);
	cout << p.getFEN() << endl;


	run_tests();
}
