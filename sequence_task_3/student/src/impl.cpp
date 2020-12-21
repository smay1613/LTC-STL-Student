#include "impl.h"

std::string reverseWords(const std::string& input)
{
    if (input.empty()){
        return input;
    }
    std::stringstream stream (input);
    std::string streamOut;

    for(std::string streamIn; stream>>streamIn; streamOut.insert(0, streamIn+' '));

    streamOut.erase(streamOut.end() - 1);
    if (*(streamOut.begin()) == ' ')
        streamOut.erase(streamOut.begin());
    return streamOut;
}
