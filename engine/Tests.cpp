#include "Tests.h"

void run_bitboard_tests() {
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
	
	assert(pop_lsb(b) == 0); // Returns lowest occupied index
	assert(popcount(b) == 2); // Checks to make sure that the number of occupied squares decreased
	assert(pop_lsb(b) == 28);
	assert(popcount(b) == 1);
	assert(pop_lsb(b) == 63);
	assert(popcount(b) == 0);

	assert(lsb(empt) == -1); // Confirms that lsb of empty board is defined -1

	std::cout << "All tests cleared" << std::endl;
}