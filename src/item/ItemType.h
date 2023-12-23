#ifndef ITEM_TYPE_H
#define ITEM_TYPE_H

#include <string>

using namespace std;

/**
 * Available item types.
*/
enum ItemType {
    none = 0,
    cosmetic,
    kitchenware,
    softDrinks,
    breakfastSpread,
    noodles,
    washing,
    fruit,
    vegetables,
};

/**
 * The highest value of `ItemType` available.
*/
const short itemTypeHighest = 8;

/**
 * Attempts to parse a number to an `ItemType`.
 * 
 * @param num The number to parse.
*/
ItemType parseItemType(const short num);

/**
 * Converts an `ItemType` into its string equivalent.
 * 
 * @param itemType The `ItemType` to convert.
*/
string itemTypeToString(const ItemType &itemType);

/**
 * Lists all item types.
*/
void listItemTypes();

#endif
