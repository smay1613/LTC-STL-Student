#include "impl.h"

#include <algorithm>
#include <stack>
#include <vector>

const std::vector<std::pair<char, char> > brackets{
    {'(', ')'}, {'[', ']'}, {'{', '}'}};

bool isValid(const std::string& source) {
  std::stack<char> result;
  for (const auto& symbol : source) {
    auto it =
        std::find_if(brackets.begin(),
                     brackets.end(),
                     [&symbol](const std::pair<char, char>& brackets_pair) {
                       return brackets_pair.first == symbol ||
                              brackets_pair.second == symbol;
                     });

    if (it != brackets.end()) {
      if (symbol == it->first) {
        result.push(symbol);
      } else if (result.empty()) {
        return false;
      } else {
        if (result.top() == it->first) {
          result.pop();
        } else {
          return false;
        }
      }
    }
  }

  return result.empty();
}
