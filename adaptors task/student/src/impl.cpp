#include "impl.h"
#include <vector>
#include <algorithm>

const std::vector<std::pair<char, char>> brackets {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'}
};

bool isValid(const std::string& source)
{
   std::stack<char> charsStack;
   bool result = true;

   for (const auto& ch : source)
   {
      for(const auto& pair: brackets){
         if (ch == pair.first){
            charsStack.push(pair.second);
         } else if (ch == pair.second) {
            if(!charsStack.empty() && pair.second == charsStack.top()) {
               charsStack.pop();
            } else {
               result = false;
               break;
            }
         }
      }

      if (!result){
         break;
      }
   }
   return result && charsStack.empty();
}
