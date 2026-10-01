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

void newFrame () {
	cout << "\n\n";
	for (array<Chunk,5> a : chunks) {
		for (Chunk c : a) cout << c.c;
		cout << "\n";
	}
}

void chunkUpdater () {
	while (GAME_RUNNING) {
		char userInput;
		if (!chunksToGen.empty() || !generatedChunks.empty()) {
			cout << "Enter option: (1) Generate Next Chunk, (2) Redo last chunk: ";
			if (!(cin >> userInput)) {
				GAME_RUNNING = false;
				break;
			}
			if (userInput == '1') {
				if (!chunksToGen.empty()) {
					vec2 v = chunksToGen.front();
					generateChunkAt(v);
					chunksToGen.pop();
					cout << "Generated chunk at (" << (int)v.x << ", " << (int)v.y << ")\n";
				} else {
					cout << "Queue empty\n";
				}
			} else if (userInput == '2') {
				if (!generatedChunks.empty()) {
					vec2 lastPosition = generatedChunks.top();
					generatedChunks.pop();
					generateChunkAt(lastPosition);
					cout << "Regenerated chunk at (" << (int)lastPosition.x << ", " << (int)lastPosition.y << ")\n";
				} else {
					cout << "Stack empty\n";
				}
			} else {
				cout << "Invalid input\n";
			}
			newFrame();
		}
	}
}

int main () {
	for (int x = 0; x < chunkDim; ++x) {
		for (int y = 0; y < chunkDim; ++y) {
			chunksToGen.push(vec2(x, y));
		}
	}

	chunkUpdateThread = new thread(chunkUpdater);


	if (chunkUpdateThread->joinable()) chunkUpdateThread->join();

	return 0;
}