#include "impl.h"
#include <vector>
#include <stack>
const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};
bool isValid(const std::string& source){
    if (source.empty() or source.size()==1)
    {
        return false;
    }
    std::stack<char> res;

    for (auto stringCh : source) {
        for (auto reg : brackets) {
            if (stringCh == reg.first)
                {
                    res.push(stringCh);
                    continue;
                }
                else if (stringCh == reg.second)
                {
                    if (res.empty() or source.at(0) == reg.second or res.top() != reg.first)
                    {
                        return false;
                    }
                    res.pop();
                    continue;
                }
            }
        }
        return res.empty();
}
