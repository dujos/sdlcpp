#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>

class Random {

public:
	static void init();
	static int get_rand(int x);
};

#endif