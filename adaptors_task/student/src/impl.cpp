#include "impl.h"
#include <vector>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source){
	std::stack<char> stack;
	auto find_pair = [](char c){
		for (auto it = brackets.cbegin() ; it != brackets.cend(); it++) {
		if (c == it->first || c == it->second)
			return it;
		}
		return brackets.cend();
	};
	
	for (auto c : source){
		auto check = find_pair(c);
		if (check != brackets.cend())
		{
			if (check->first == c)
				stack.push(c);
			else if (!stack.empty() && stack.top() == check->first && c == check->second)
				stack.pop();
			else
				return false;
		}
	}
	return stack.empty();
}