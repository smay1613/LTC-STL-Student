#include "impl.h"
#include <vector>
#include <algorithm>
#include <stack>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
    bool isValid = true;
    std::stack<char> stack;
    std::for_each(source.begin(),source.end(), [&stack,&isValid](const char& ch)
    {
       std::for_each(brackets.begin(),brackets.end(),[&ch,&stack,&isValid](const std::pair<char, char>& pair)
       {
          if(ch == pair.first)
          {
             stack.push(ch);
          }

          if(ch == pair.second)
          {
              if ( stack.empty() )
              {
                  isValid = false;
                  return;
              }
              else if( stack.top() != pair.first )
              {
                  isValid = false;
                  return;
              }
              else
              {
                  stack.pop();
              }
          }
       });
    });
    return (isValid && stack.empty());
}
