#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <cctype>
#include <string>

using namespace std;

namespace StringUtils {
/**
 * Converts a string to lowercase.
 * 
 * @param str The string to convert.
 * @returns The lowercased string.
*/
string tolower(const string &str);
} // namespace StringUtils

#endif
