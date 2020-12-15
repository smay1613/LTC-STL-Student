#include "impl.h"

std::string reverseWords(const std::string& input) {
  std::stringstream ss(input);
  const std::deque<std::string> words{std::istream_iterator<std::string>(ss),
                                      std::istream_iterator<std::string>()};
  std::stringstream output_ss;
  std::copy(words.rbegin(),
            words.rend(),
            std::ostream_iterator<std::string>(output_ss, " "));

  std::string str = output_ss.str();

  if (!str.empty())
    str.pop_back();

  return str;
}
