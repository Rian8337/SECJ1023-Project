#ifndef ITEM_SORT_METHOD_H
#define ITEM_SORT_METHOD_H

#include <string>

using namespace std;

/**
 * Available sorting methods when processing items.
*/
enum ItemSortMethod {
    sortById = 1,
    sortByName,
    sortByPriceSmallestToHighest,
    sortByPriceHighestToSmallest,
    sortByStockSmallestToHighest,
    sortByStockHighestToSmallest,
};

/**
 * The highest value of `ItemSortMethod` available.
*/
const short itemSortHighest = 6;

/**
 * Attempts to parse a number to an `ItemSortMethod`.
 * 
 * @param num The number to parse.
*/
ItemSortMethod parseSortMethod(const short num);

/**
 * Converts an `ItemSortMethod` into its string equivalent.
 * 
 * @param sortMethod The `ItemSortMethod` to convert.
*/
string itemSortMethodToString(const ItemSortMethod &sortMethod);

/**
 * Lists all sorting methods.
*/
void listSortMethods();

#endif
