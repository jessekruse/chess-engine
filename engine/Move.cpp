#include "Move.h"

Move build_move(Move from, Move to, Move Flags) {
	return (from | (to << 6) | (Flags << 12));
}

Move get_from(Move m) {
	return (m & 0x3f);
}

Move get_to(Move m) {
	return (m >> 6) & 0x3f;
}

Move get_flags(Move m) {
	return (m >> 12) & 0x0f;
}

