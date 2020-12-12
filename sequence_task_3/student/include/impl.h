#pragma once
#include <sstream>
#include <iostream>
#include <deque>
#include <iterator>
#include <vector>

/**
 * @todo Implement function that will reverse words in a sentence
 * @example "Hello there" -> "there Hello"
 * @param input - sentence with words splitted by spaces
 * @return Sentence with reversed order of words
 *
 * @warning YOU MUST USE STRING STREAMS AND STREAM ITERATORS!
 */
std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

std::string reverseWords(const std::string& input)
{
   std::string result{};

   if (!input.empty())
   {
      std::stringstream ss(input);

      std::deque<std::string> words{std::istream_iterator<std::string>(ss),std::istream_iterator<std::string>()};

      std::ostringstream oss{};
      std::copy(words.rbegin(), words.rend(), std::ostream_iterator<std::string>(oss, " "));

      std::string tempStr = oss.str();
      result = std::move(trim(tempStr));
   }

   return result;
}
