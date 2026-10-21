// engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include "ChessFunctions.h"
#include "bitboard.h"

using namespace std;

int main() {
	
	Bitboard b = RANK_8;

	printBB(b);

	cout << lsb(b) << endl;

}
