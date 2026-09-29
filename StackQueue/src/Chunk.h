#pragma once

#include <chrono>
#include <ctime>
#include <thread>
#include <string>

struct Chunk {
	Chunk () {
		using namespace std;
		
		srand(time(0));
		float r1 = rand() / (float)RAND_MAX * 2 - 1;
		this_thread::sleep_for(chrono::milliseconds(500 + (int)(r1 * 500)));

		string options = " #!?-|";
		int r2 = rand() % options.size();
	}
	char c;
};