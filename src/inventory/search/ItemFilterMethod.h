#ifndef ITEM_FILTER_METHOD_H
#define ITEM_FILTER_METHOD_H

#include <string>

using namespace std;

/**
 * Available filtering methods when processing items.
*/
enum ItemFilterMethod {
    filterByName = 1,
    filterByDescription,
};

/**
 * The highest value of `ItemFilterMethod` available.
*/
const short itemFilterHighest = 2;

/**
 * Attempts to parse a number to an `ItemFilterMethod`.
 * 
 * @param num The number to parse.
*/
ItemFilterMethod parseFilterMethod(const short num);

/**
 * Converts an `ItemFilterMethod` into its string equivalent.
 * 
 * @param filterMethod The `ItemFilterMethod` to convert.
*/
string itemFilterMethodToString(const ItemFilterMethod &filterMethod);

/**
 * Lists all filter methods.
*/
void listFilterMethods();

#endif
