#pragma once
#include <string>
#include <stack>
#include <iostream>

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
bool isValid(const std::string& source)
{
   std::stack<char> charsStack;
   bool result = true;

   auto checkCloseBrackets{[&charsStack](const char ch){
         if (!charsStack.empty() && ch == charsStack.top())
         {
            charsStack.pop();
            return true;
         }
         else
         {
            return false;
         }
      }};

   for (const char& ch : source)
   {
      switch (ch) {
      case '(':
      case '[':
      case '{':
         charsStack.push(ch);
         break;
      case ')':
         result = checkCloseBrackets('(');
         break;
      case ']':
         result = checkCloseBrackets('[');
         break;
      case '}':
         result = checkCloseBrackets('{');
         break;
      default:
         continue;
         break;
      }

      if (!result){
         break;
      }
   }
   return result && charsStack.empty();
}
