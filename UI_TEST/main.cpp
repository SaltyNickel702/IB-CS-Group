#include <iostream>
#include <thread>
#include <chrono>
#include "UI.h"

using namespace std;

int main () {
	UI u(100,20);
	u.fillChar = " ";

	UI::Sprite* S = new UI::Sprite(7,5);
	string sStr = 	R"( /\_/\ )"
					R"(((@v@)))"
					R"(():::())"
					R"( VV-VV )";

	S->importFromString(sStr, "\033[31m");
	
	u.addSprite(S);
	S->pos[1] = -5;
	u.addSprite(S);

	int i = 26;
	while (i--) {
		u.display();
		S->pos[0]++;
		S->pos[1]++;
		this_thread::sleep_for(chrono::milliseconds(250));
	}
}