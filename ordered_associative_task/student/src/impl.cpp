#include "impl.h"
std::map<size_t,size_t> mapConverter={{29,1},{49,2},{69,3},{89,4},{SIZE_MAX,5}};

size_t convertMarkTo5PointSystem(size_t markIn100Point){
     return mapConverter.lower_bound(markIn100Point)->second;
}
