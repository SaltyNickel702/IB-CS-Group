#pragma once

#include <vector>
#include <map>
#include <string>


struct Resolution {
	Resolution ();

	virtual std::string resolve ();
	std::string resolveText;
};

struct Question : Resolution {
	Question (std::string question);
	
	void addOption (std::string answer, Resolution resolution);
	
	std::vector<std::string> getOptions ();

	private:
		std::map<std::string,Resolution> options;
		std::string question;
};