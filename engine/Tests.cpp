#include "Tests.h"

void run_tests() {

	//////////////////////////
	// Bitboard.cpp tests
	//////////////////////////

	Bitboard empt = 0;

	assert(sN(empt) == empt); // Shifting north on empty does nothing
	assert(sE(empt) == empt); // Shifting east on empty does nothing
	assert(sS(empt) == empt); // Shifting south on empty does nothing
	assert(sW(empt) == empt); // Shifting west on empty does nothing

	Bitboard b = FILE_H;
	assert(sE(b) == empt); // Shifting east on FILE_H returns empty

	b = FILE_A;
	assert(sW(b) == empt); // Shifting west on FILE_A returns empty

	b = RANK_8;
	assert(sN(b) == empt); // Shifting north on RANK_8 returns empty

	b = RANK_1;
	assert(sS(b) == empt); // Shifting south on RANK_1 returns empty

	b = sqIndextoBB(squareIndex('a','1'));
	assert(sN(b) == sqIndextoBB(squareIndex('a', '2'))); // a1 north gives a2
	assert(sE(b) == sqIndextoBB(squareIndex('b', '1'))); // a1 east gives b1

	assert(sqIndextoBB(squareIndex('a', '8')) == 0x0100000000000000); // confirm hex value of a8 bitboard

	b = 0x1;
	assert(lsb(b) == 0); // Least significant bit of 0x1 returns index 0
	b = 0x80;
	assert(lsb(b) == 7); // least significant bit of 0x80 returns index 7
	b = 1ULL << 63;
	assert(lsb(b) == 63); // least significant bit of 1ULL << 63 is 63

	Bitboard a1 = sqIndextoBB(squareIndex('a', '1'));
	Bitboard e4 = sqIndextoBB(squareIndex('e', '4'));
	Bitboard h8 = sqIndextoBB(squareIndex('h', '8'));
	b = a1 | e4 | h8;

	assert(popcount(b) == 3); // Count of occupied squares for {a1, e4, h8} is 3
	

	assert(lsb(empt) == -1); // Confirms that lsb of empty board is defined -1


	//////////////////////////////////
	// Position.cpp Tests
	//////////////////////////////////

	FEN fStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	FEN fEnPassant = "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR b KQkq f6 0 3";
	FEN fEndGame = "8/4k3/8/4P3/4K3/8/8/8 w - - 0 1";
	FEN fFullMove = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";

	Position p;
	p.loadFEN(fStart);

	assert(p.sideToMove == WHITE);
	assert(p.canCastle == (K | Q | k | q));
	assert(p.enPassant == 0);
	assert(p.halfmove == 0);
	assert(p.fullmove == 1);
	assert(popcount(p.pieces[allWhite]) == 16);
	assert(popcount(p.pieces[allBlack]) == 16);
	assert(popcount(p.pieces[allPieces]) == 32);
	assert(p.getFEN() == fStart);

	p.loadFEN(fEnPassant);
	assert(p.sideToMove == BLACK);
	assert(p.enPassant == sqIndextoBB(squareIndex('f', '6')));
	assert(p.pieces[allPieces] == (p.pieces[allWhite] | p.pieces[allBlack]));
	assert((p.pieces[allWhite] & p.pieces[allBlack]) == 0);
	assert(p.getFEN() == fEnPassant);

	p.loadFEN(fEndGame);
	assert(p.sideToMove == WHITE);
	assert(p.canCastle == 0);
	assert(p.getFEN() == fEndGame);

	p.loadFEN(fFullMove);
	assert(p.sideToMove == WHITE);
	assert(p.canCastle == 0);
	assert(p.halfmove == 0);
	assert(p.fullmove == 10);
	assert(p.getFEN() == fFullMove);

	
	/////////////////////////////
	// Move.cpp tests
	/////////////////////////////

	move_t from = squareIndex('e', '2');
	move_t to = squareIndex('e', '4');
	move_t flag = DOUBLE_PAWN_PUSH;

	Move full_move(from, to, flag);
	assert(full_move.m == 0x170C);

	assert(full_move.get_from() == squareIndex('e', '2'));
	assert(full_move.get_to() == squareIndex('e', '4'));
	assert(full_move.get_flag() == DOUBLE_PAWN_PUSH);

	full_move.m = 0xFE31;
	assert(full_move.isCapture());
	assert(full_move.isPromotion());

	full_move.m = 0x5AE4;
	assert(full_move.isCapture());
	assert(full_move.isPromotion() == 0);

	full_move.m = 0x170C;
	assert(full_move.isCapture() == 0);
	assert(full_move.isPromotion() == 0);


	///////////////////////////////
	// Attacks.cpp tests
	///////////////////////////////
	int countKnight = 0;
	int countKing = 0;
	int countWPawn = 0;
	int countBPawn = 0;

	for (int s = 0; s < 64; ++s) {
		countKnight += popcount(knightAttacks[s]);
		countKing += popcount(kingAttacks[s]);
		countWPawn += popcount(pawnAttacks[WHITE][s]);
		countBPawn += popcount(pawnAttacks[BLACK][s]);
	}

	assert(countKnight == 336);
	assert(countKing == 420);
	assert(countWPawn == 98);
	assert(countBPawn == 98);

	
	assert(popcount(knightAttacks[squareIndex('a','1')]) == 2);
	assert(popcount(knightAttacks[squareIndex('b','1')]) == 3);
	assert(popcount(knightAttacks[squareIndex('e','4')]) == 8);
	assert(popcount(knightAttacks[squareIndex('h','8')]) == 2);

	int countRook = 0;
	int countBishop = 0;
	int countQueen = 0;

	for (int s = 0; s < 64; ++s) {
		countRook += popcount(rookAttacks(s, 0));
		countBishop += popcount(bishopAttacks(s, 0));
		countQueen += popcount(queenAttacks(s, 0));
	}

	assert(countRook == 896);
	assert(countBishop == 560);
	assert(countQueen == 1456);

	assert(popcount(bishopAttacks(squareIndex('a', '1'), 0)) == 7);
	assert(popcount(bishopAttacks(squareIndex('d', '4'), 0)) == 13);

	int sq = squareIndex('d', '4');
	b = sqIndextoBB(sq);
	Bitboard occupied = sqIndextoBB(squareIndex('d','6'));
	fillSq(occupied, squareIndex('g','4'));

	assert(popcount(rookAttacks(sq, occupied)) == 11);
	assert(isInBB(rookAttacks(sq, occupied), squareIndex('d', '6')));
	assert(isInBB(rookAttacks(sq, occupied), squareIndex('g', '4')));
	assert(!isInBB(rookAttacks(sq, occupied), squareIndex('d', '7')));
	assert(!isInBB(rookAttacks(sq, occupied), squareIndex('h', '4')));


	/////////////////////////
	// Movegen.cpp Tests
	/////////////////////////
	MoveList ml;

	// Start position checks
	p.loadFEN(fStart);
	generateMoves(p, ml);
	assert(ml.count == 20);

	p.sideToMove = BLACK;
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 20);

	FEN fRookKingTest = "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1";
	
	p.loadFEN(fRookKingTest);
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 26);

	// Promotion checks
	p.loadFEN("1n5k/P7/8/8/8/8/6K1/8 w - - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 16);

	p.loadFEN("8/6k1/8/8/8/8/p7/1N5K b - - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 16);

	p.loadFEN("8/PPPPPPPP/8/k7/8/8/8/K7 w - - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 35);

	p.loadFEN("8/8/8/K7/8/k7/pppppppp/8 b - - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 35);

	// En passant checks

	p.loadFEN("4k3/8/8/3pP3/8/8/8/4K3 w - d6 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 7);

	p.loadFEN("4k3/8/8/8/3Pp3/8/8/4K3 b - d3 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 7);

	// Blocked push checks

	p.loadFEN("4k3/8/8/8/8/4n3/4P3/4K3 w - - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 4);

	p.loadFEN("4k3/8/8/8/4n3/8/4P3/4K3 w - - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 5);

	p.loadFEN("4k3/4p3/4N3/8/8/8/8/4K3 b - - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 4);

	p.loadFEN("4k3/4p3/8/4N3/8/8/8/4K3 b - - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 5);

	// Castling checks

	p.loadFEN("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 26);

	p.loadFEN("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 26);

	p.loadFEN("r3k2r/8/8/8/8/8/8/R3K2R w - - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 24);

	p.loadFEN("r3k2r/8/8/8/8/8/8/R3K2R w Kq - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 25);

	p.loadFEN("r3k2r/8/8/8/8/8/8/R3K2R b Kq - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 25);

	p.loadFEN("r3k2r/8/8/8/8/8/8/RN2K2R w KQkq - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 25);

	p.loadFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 48);

	p.loadFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1");
	ml.clear();
	generateMoves(p, ml);
	assert(ml.count == 43);

	////////////////////////////////
	// makeMove tests
	////////////////////////////////

	from = squareIndex('g', '1');
	to = squareIndex('f', '3');
	flag = QUIET_MOVE;
	
	Move m(from, to, flag);

	p.loadFEN(fStart);
	p.makeMove(m);
	assert(p.getFEN() == "rnbqkbnr/pppppppp/8/8/8/5N2/PPPPPPPP/RNBQKB1R b KQkq - 1 1");
	assert((p.pieces[allWhite] & p.pieces[allBlack]) == 0);
	assert(p.pieces[allPieces] == (p.pieces[allWhite] | p.pieces[allBlack]));

	FEN fEPTest = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
	p.loadFEN(fEPTest);
	
	m.update("g8", "f6", QUIET_MOVE);
	p.makeMove(m);
	assert(p.getFEN() == "rnbqkb1r/pppppppp/5n2/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 1 2");
	assert((p.pieces[allWhite] & p.pieces[allBlack]) == 0);
	assert(p.pieces[allPieces] == (p.pieces[allWhite] | p.pieces[allBlack]));

	p.loadFEN("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2");
	m.update("e4", "d5", CAPTURE);
	p.makeMove(m);
	assert((p.pieces[allWhite] & p.pieces[allBlack]) == 0);
	assert(p.pieces[allPieces] == (p.pieces[allWhite] | p.pieces[allBlack]));

	p.loadFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 5 1");
	m.update("e5", "f7", CAPTURE);
	p.makeMove(m);
	assert((p.pieces[allWhite] & p.pieces[allBlack]) == 0);
	assert(p.pieces[allPieces] == (p.pieces[allWhite] | p.pieces[allBlack]));


	std::cout << "All tests cleared" << std::endl;
}

