#include "Question.h"

using namespace std;

Resolution::Resolution () {};
string Resolution::resolve () { return resolveText; };

Question::Question (string q) { question = q; };
void Question::addOption (string a, Resolution r) {
	
}