#include <stdlib.h>
#include <time.h>

#include "Random.h"

using namespace game;

Random::Random() {
	srand(static_cast<unsigned int>(time(NULL)));
}

int Random::Next() const {
	return rand();
}