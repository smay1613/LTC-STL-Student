#include "impl.h"
#include <vector>
#include <stack>
#include <algorithm>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
   auto brBegin = brackets.cbegin();
   auto brEnd = brackets.cend();

   std::stack<char> bracketsScope;

   std::for_each(source.cbegin(), source.cend(), [&](const char& ch)
   {
      if(std::any_of(brBegin, brEnd, [&ch](const std::pair<char,char>& pair){ return ch == pair.first || ch == pair.second; }))
      {
         auto found = std::find_if(brBegin, brEnd, [&ch](const std::pair<char,char>& pair){return pair.second == ch;});
         bool isClose = (!bracketsScope.empty() && bracketsScope.top() == found->first);

         //Is it normal from the reading point of view?
         //isClose ? bracketsScope.pop() : bracketsScope.push(ch);
         if(isClose)
         {
            bracketsScope.pop();
         }
         else
         {
            bracketsScope.push(ch);
         }
      }
   });

   return bracketsScope.empty();
}
