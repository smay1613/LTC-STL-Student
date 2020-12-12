#pragma once
#include <list>
#include <iostream>

/** @todo implement effective list rotation algorithm
 *
 * T - value type
 * BI - iterator type
 *
 * @param list - container, for which rotation will be done
 * @param begin - begin of sequence that will be rotated
 * @param end - end of a sequence that will be rotated
 * @param new_begin - new position of rotated sequence
 *
 * @note See https://en.cppreference.com/w/cpp/algorithm/rotate
 */
template<class T, class BI>
void rotate(std::list<T>& list, BI begin, BI new_begin, BI end) {
    std::list<T> tempList;
    if (new_begin != end) {
        while(std::distance(begin, new_begin)) {
            tempList.push_back(*begin);
            begin = list.erase(begin);
            //std::cout << std::distance(begin, new_begin) << "\n";
        }
        list.splice(end, tempList);
    }
}
