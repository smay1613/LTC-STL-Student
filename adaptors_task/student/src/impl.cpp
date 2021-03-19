#include "impl.h"

#include <stack>
#include <vector>
#include <utility>
#include <algorithm>

namespace {

using BracketsPair = std::pair<char, char>;
using BracketsDictionary = std::vector<BracketsPair>;
const BracketsDictionary brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

} // namespace

bool isValid(const std::string& source) {

    std::stack<char> s;
    for (auto c : source) {
        auto iter = std::find_if(brackets.cbegin(), brackets.cend(), [c](const BracketsPair& p) {
            return p.first == c || p.second == c;
        });

        if (iter == brackets.end()) {
            continue;
        }

        if (iter->first == c) {
            s.push(c);
            continue;
        }

        if (s.empty() || iter->first != s.top()) {
            return false;
        }

        s.pop();
    }
    return s.empty();
}
