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
	
	FEN fCastle = "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1";

	Position p;
	p.loadFEN(fCastle);
	MoveList ml;

	generateMoves(p, ml);

	p.print();

	cout << ml.count << endl;



	run_tests();
}
