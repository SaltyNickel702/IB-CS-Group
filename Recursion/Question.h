#pragma once

#include <vector>
#include <map>
#include <string>


struct Resolution {
	Resolution ();
	Resolution (std::string text);

	virtual std::string resolve ();
	std::string resolveText;

	Question* optQuestion;
};

struct Question : Resolution {
	Question (std::string question);
	
	void addOption (std::string answer, Resolution resolution);
	
	std::vector<std::string> getOptions ();
	std::string resolve () override; // Asks the question

	private:
		std::map<std::string,Resolution> options;
		std::string question;
};