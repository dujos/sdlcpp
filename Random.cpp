#include "Random.h"

void Random::init() {
	std::srand((int) std::time(NULL));
}

int Random::get_rand(int x) {
	return (int)(double) x * std::rand()/(RAND_MAX+1);
}