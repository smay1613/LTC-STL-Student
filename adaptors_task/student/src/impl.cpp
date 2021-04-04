#include "impl.h"
#include <vector>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};
using bracketPair = const std::pair<char, char> &;

bool isOpenBracket(const char ch) {
    auto openBracket = std::find_if(brackets.begin(), brackets.end(),
                                    [&ch](bracketPair br) {
                                        return ch == br.first;
                                     });

    return openBracket != brackets.end();
}

bool isClosedBracket(const char ch) {
    auto closedBracket = std::find_if(brackets.begin(), brackets.end(),
                                    [&ch](bracketPair br) {
                                        return ch == br.second;
                                     });

    return closedBracket != brackets.end();
}

bool isMirrored(const char ch1, const char ch2) {
    auto mirrored = std::find_if(brackets.begin(), brackets.end(),
                                    [&ch1, &ch2](bracketPair br) {
                                        return ch1 == br.first && ch2 == br.second;
                                     });

    return mirrored != brackets.end();
}

void validation(std::stack<char> & bracketStack, bool & isValid,const char ch) {
    if (!isValid) return;

    if (isOpenBracket(ch)) {
       bracketStack.push(ch);
     }

    if (isClosedBracket(ch)) {
        if (bracketStack.empty()) {
            isValid = false;
            return;
        }
        if (!isMirrored(bracketStack.top(), ch)) {
            isValid = false;
            return;
        }
        bracketStack.pop();
    }
}

bool isValid(const std::string& source) {
    std::stack<char> bracketStack;
    bool isValid = true;

    for_each(source.begin(), source.end(),
             [&bracketStack, &isValid](const char ch) {
             validation(bracketStack, isValid, ch);
    });

    return isValid && bracketStack.empty();
}
