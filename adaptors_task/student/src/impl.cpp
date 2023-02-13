#include "impl.h"
#include <vector>
#include <tuple>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

std::pair<char, char> get_matching_brackets_pair(char c) {
	for (auto &bracket_pair: brackets) {
		if (c == bracket_pair.first || c == bracket_pair.second)
			return bracket_pair;
		}
	return {};
}


bool isValid(const std::string& source){
	std::stack<char> stack;
	for (auto c : source){
		char openBracket, closingBracket;
		std::tie(openBracket, closingBracket) = get_matching_brackets_pair(c);
		if (openBracket != closingBracket)
		{
			if (c == openBracket) {
				stack.push(c);
			}
			else if (!stack.empty() && stack.top() == openBracket && c == closingBracket  ) {
				stack.pop();
			}
			else {
				return false;
			}
		}
	}
	return stack.empty();
}