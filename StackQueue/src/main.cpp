#include "Chunk.h"

#include <array>
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
stack<vec2> generatedChunks;
thread* chunkUpdateThread;

void generateChunkAt (vec2 position) {
	Chunk c(true);
	chunks.at((int)position.x).at((int)position.y) = c;
	generatedChunks.push(position);
}

void chunkUpdater () {
	while (GAME_RUNNING) {
		char userInput;
		if (!chunksToGen.empty() || !generatedChunks.empty()) {
			cout << "Enter option: (1) Generate Next Chunk, (2) Redo last chunk";
			cin.get(userInput); 
			if (userInput == '1') {
				if (!chunksToGen.empty()) {
					vec2 v = chunksToGen.front();
					generateChunkAt(v);
					chunksToGen.pop();
				} else {
					cout << "Queue empty";
				}
			} else if (userInput == '2') {
				if (!generatedChunks.empty()) {
					vec2 lastPosition = generatedChunks.top();
					generatedChunks.pop();
					generateChunkAt(lastPosition);
				} else {
					cout << "Stack empty";
				}
			} else {
				cout <<  "Invalid Input";
			}
		}
	}
}

void newFrame () {
	
}

int main () {
	chunkUpdateThread = new thread(chunkUpdater);


	if (chunkUpdateThread->joinable()) chunkUpdateThread->join();

	return 0;
}