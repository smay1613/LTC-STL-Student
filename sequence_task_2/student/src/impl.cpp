#include "impl.h"

template<class T, class BI>
void rotate(std::list<T>& list, BI begin, BI new_begin, BI end) {
    list.splice(begin, list, new_begin, end);
}

template void rotate(std::list<size_t>&, std::list<size_t>::iterator,
    std::list<size_t>::iterator, std::list<size_t>::iterator);
