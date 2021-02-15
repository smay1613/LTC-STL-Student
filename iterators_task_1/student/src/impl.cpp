#include "impl.h"
#include <vector>
#include <algorithm>

using namespace std;

string reverseWords(const string& input) {
    istringstream iss {input};
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
    ostringstream oss;

    copy(tokens.rbegin(),
         tokens.rend() - 1,
         ostream_iterator<string>(oss, " "));

    if (tokens.size() > 0) {
        oss << tokens.front();
    }
    return oss.str();
}
