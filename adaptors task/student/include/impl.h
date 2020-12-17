#pragma once
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

/**
 * @todo isValid - check if given expression is valid - all open brackets are closed
 * by CORRESPONDING closed bracket.
 *
 * @param source - expression that will contain brackets
 * of three types: "()"/"[]"/"{}".
 * May contain other symbols or may not contain anything.
 *
 * @return true if expression is valid
 */

std::vector<std::pair<char, char>> braces_collection =
{
    {'{', '}'},
    {'(', ')'},
    {'[', ']'}
};

bool isValid(const std::string& source)
{
    std::stack<char> char_sequence;
    for(auto& ch : source)
    {
        auto it = std::find_if(braces_collection.begin(), braces_collection.end(), [&ch](std::pair<char, char> braces)
        {
            return (braces.first == ch || braces.second == ch);
        });

        if(it != braces_collection.end())
        {
            if(it->first == ch) char_sequence.push(ch);
            else if(it->second == ch)
            {
                if(!char_sequence.empty() && char_sequence.top() == it->first) char_sequence.pop();
                else return false;
            }
        }
    }

    return char_sequence.empty();
}

