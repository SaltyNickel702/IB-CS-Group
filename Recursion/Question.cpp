#include "Question.h"
#include <iostream>
#include <format>

using namespace std;

string getInput () {
	cout << "> ";
	string s;
	getline(cin,s);
	return s;
}

Resolution::Resolution (string s) : resolveText(s) {};
Resolution::Resolution () : Resolution("") {};
string Resolution::resolve () {
	cout << resolveText << endl;
	if (optQuestion) resolveText = optQuestion->resolve();
	return resolveText;
};

Question::Question (string q) : question(q) {};
void Question::addOption (string a, Resolution r) {
	options.at(a) = r;
}
vector<string> Question::getOptions () {
	vector<string> o;
	for (auto [key, _] : options) {
		o.push_back(key);
	}
	return o;
}
string Question::resolve () {
	vector<string> opts = getOptions();
	cout << format("Q: {}\n", question);
	cout << "Options:\n" << endl;
	for (int i = 0; i < opts.size(); i++) {
		cout << format("\t{}: {}\n",i,opts.at(i));
	}
	
	bool inpAccepted = false;
	while (!inpAccepted) {
		string s = getInput();
		if (s == "exit" || s == "quit") break;
		
		try {
			int i = std::stoi(s);
			if (i < 0 || i >= opts.size()) continue;
			return opts.at(i);
		} 
		catch (const std::invalid_argument& e) {} 
		catch (const std::out_of_range& e) {}
	}
	return "Quit Help Desk";
};