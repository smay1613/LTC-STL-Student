#include "impl.h"
#include <vector>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};


bool isValid(const std::string& source)
{
    std::stack<char> char_sequence;
    for(const auto& ch : source)
    {
        auto it = std::find_if(brackets.begin(), brackets.end(), [&ch](std::pair<char, char> braces)
        {
            return (braces.first == ch || braces.second == ch);
        });

        bool isBracket = (it != brackets.end());
        bool isClosed  = (!char_sequence.empty() && char_sequence.top() == it->first);

        if(isBracket)
        {
            if(it->first == ch) char_sequence.push(ch);
            else if(it->second == ch)
            {
                if(isClosed) char_sequence.pop();
                else return false;
            }
        }
    }
    return char_sequence.empty();
}


