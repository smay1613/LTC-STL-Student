#include "impl.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

std::string reverseWords(const std::string& input)
{
	if(input.empty())
		return input;
	std::string input_copy{input};

	input_copy.erase(std::find_if(input_copy.rbegin(), input_copy.rend(),
					[](unsigned char ch)
					{
						return !std::isspace(ch);
					}).base(), input_copy.end());

	input_copy.erase(input_copy.begin(), std::find_if(input_copy.begin(), input_copy.end(),
					[](unsigned char ch)
					{
						return !std::isspace(ch);
					}));

	if(input_copy.empty())
		return input_copy;

	std::stringstream ssInput{std::move(input_copy)};
	std::stringstream ssOutput;
	std::string result;
	std::vector<std::string> words;
	std::copy(std::istream_iterator <std::string> (ssInput),
			  std::istream_iterator <std::string> (),
			  std::back_inserter(words)
			  );
	std::copy(std::reverse_iterator<std::vector<std::string>::iterator>(words.rbegin()),
			  std::reverse_iterator<std::vector<std::string>::iterator>(words.rend()),
			  std::ostream_iterator<std::string>(ssOutput, " ")
			  );
	result = ssOutput.str();
	result.pop_back();
	return result;
}