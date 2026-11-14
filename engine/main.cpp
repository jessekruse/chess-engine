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
	p.loadFEN("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2");

	p.loadFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 5 1");

	m.update("e5", "f7", CAPTURE);

	p.print();
	cout << p.getFEN() << endl;

	p.makeMove(m);

	p.print();
	cout << p.getFEN() << endl;

	run_tests();
}
