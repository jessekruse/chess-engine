// engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include "greet.h"
#include "ChessFunctions.h"

using namespace std;

int main() {
	cout << countBits(0) << endl; // Expect 0 bits set
	cout << countBits(1) << endl; // Expect 1 bit set (the first)
	cout << countBits(1ULL << 63) << endl; // Expect 1 bit set (the last)
	cout << countBits(~0ULL) << endl; // Expect 64 bits set 
}
