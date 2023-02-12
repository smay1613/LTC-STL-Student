#include "impl.h"
#include <vector>
#include <tuple>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

std::pair<char, char> get_brackets(char c) {
	for (auto &bracket: brackets) {
		if (c == bracket.first || c == bracket.second)
			return std::make_pair(bracket.first, bracket.second);
		}
	return std::pair<char, char>();
}


bool isValid(const std::string& source){
	std::stack<char> stack;
	for (auto c : source){
		char lbracket, rbracket;
		std::tie(lbracket, rbracket) = get_brackets(c);
		if (lbracket != rbracket)
		{
			if (lbracket == c) {
				stack.push(c);
			}
			else if (!stack.empty() && stack.top() == lbracket && c == rbracket) {
				stack.pop();
			}
			else {
				return false;
			}
		}
	}
	return stack.empty();
}