#include "impl.h"
#include <vector>
#include <algorithm>

std::string reverseWords(const std::string& input){
    std::stringstream sstream(input);
    std::vector<TokenString> tokens {std::istream_iterator<TokenString>{sstream}, std::istream_iterator<TokenString>{}};


    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](TokenString token){
        return token.isEmpty();
    }), tokens.end());

    std::vector<std::string> reversedTokens;
    std::transform(tokens.rbegin(), tokens.rend(), std::back_inserter(reversedTokens), [](const TokenString& token){
        return token.getToken();
    });

    sstream = std::stringstream();
    std::copy(reversedTokens.begin(), reversedTokens.end(), std::ostream_iterator<std::string>{sstream, " "});

    std::string result{sstream.str()};
    if (!result.empty()){
        result.pop_back();
    }
    return result;
}

const std::string& TokenString::getToken() const {
    return m_data;
}

std::string &TokenString::getToken() {
    return m_data;
}

bool TokenString::isEmpty() const {
    return m_data.empty();
}
