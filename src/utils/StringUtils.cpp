#include "StringUtils.h"

#include <string>

using namespace std;

namespace StringUtils {
string tolower(const string &str) {
    string lowercaseStr;
    lowercaseStr.resize(str.size());

    for (char c : str) {
        lowercaseStr += std::tolower(c);
    }

    return lowercaseStr;
}
} // namespace StringUtils
