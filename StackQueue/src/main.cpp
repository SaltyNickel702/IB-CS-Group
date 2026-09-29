#include "Chunk.h"

#include <iostream>
#include <stack>
#include <queue>
#include <functional>
#include <vector>
#include <thread>

using namespace std;

bool GAME_RUNNING = true;

struct vec2 {
	vec2 (int X, int Y) : x(X), y(Y) {};
	vec2 () : vec2(0,0) {};

	float x, y;
};

int chunkSize = 3;
int chunkDim = 5;
array<array<Chunk,5>,5> chunks;

queue<vec2> chunksToGen;
thread* chunkUpdateThread;
void chunkUpdater () {
	while (GAME_RUNNING) {
		if (!chunksToGen.empty()) {
			vec2 v = chunksToGen.front();
			Chunk c(true);
			chunks.at(v.x).at(v.y) = c;
			chunksToGen.pop();
		}
	}
}

void newFrame () {
	
}

int main () {
	chunkUpdateThread = new thread(chunkUpdater);

	return 0;
}