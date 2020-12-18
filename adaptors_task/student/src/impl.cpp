#include "impl.h"
#include <vector>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

static int find_i(const char& finding,
              const std::vector<std::pair<char, char>> brackets)
{
    for(int i = 0; i < brackets.size(); ++i) {
        if(brackets[i].second == finding) {
            return i;
        }
    }

    return -1;
}

bool isValid(const std::string& source)
{
    std::stack<char> stk;

    for(const char& i: source) {
        switch (i) {
            case '[':
                stk.push('[');
                break;
            case ']': {
                if(stk.empty())
                    return false;

                int i = find_i(']', brackets);
                if(i == -1) {
                    return false;
                }

                char c = stk.top();
                if(c == brackets[i].first) {
                    stk.pop();
                    break;
                } else {
                    return false;
                }
            }
            case '{':
                stk.push('{');
                break;
            case '}': {
                if(stk.empty())
                    return false;

                int i = find_i('}', brackets);
                if(i == -1) {
                    return false;
                }

                char c = stk.top();
                if(c == brackets[i].first) {
                    stk.pop();
                    break;
                } else {
                    return false;
                }
            }
            case '(':
                stk.push('(');
                break;
            case ')': {
                if(stk.empty())
                    return false;

                int i = find_i(')', brackets);
                if(i == -1) {
                    return false;
                }

                char c = stk.top();
                if(c == brackets[i].first) {
                    stk.pop();
                    break;
                } else {
                    return false;
                }
            }
        }
    }

    if(!stk.empty())
        return false;

    return true;
}
