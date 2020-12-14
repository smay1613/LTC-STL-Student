#include "impl.h"
#include <vector>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
    std::stack<char> stackChecker;

    for (auto nextSymbol: source) {
        for (auto nextPair: brackets) {
            if (nextSymbol == nextPair.first) {
                stackChecker.push(nextSymbol);
            }
            if (nextSymbol == nextPair.second) {
                if (!stackChecker.empty() && stackChecker.top() == nextPair.first){
                    stackChecker.pop();
                } else {
                    stackChecker.push(nextSymbol);
                }
            }
        }
    }

    if (stackChecker.empty()){ return true; }
    else { return false; }
}
