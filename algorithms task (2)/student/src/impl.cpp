#include "impl.h"
bool startsWith(const std::string& source, const std::string& prefix){
    return prefix.compare(source.substr(0, prefix.size())) == 0 ? true : false;
}
