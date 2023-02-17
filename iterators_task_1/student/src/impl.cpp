#include "impl.h"

std::string reverseWords(const std::string& input) {
	std::stringstream ss(input);
	std::string reversed, word;
	while (ss >> word) {
		if (!reversed.empty()){
			reversed = " " + reversed;
		}
		reversed = word + reversed;
	}
	return reversed;
}

