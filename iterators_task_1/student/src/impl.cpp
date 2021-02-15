#include "impl.h"
#include <vector>
#include <algorithm>

using namespace std;

string reverseWords(const string& input) {
    istringstream iss {input};
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
    ostringstream oss;

    if (tokens.empty()) {
        return "";
    }

    copy(tokens.rbegin(),
         tokens.rend() - 1,
         ostream_iterator<string>(oss, " "));

    oss << tokens.front();
    return oss.str();
}
